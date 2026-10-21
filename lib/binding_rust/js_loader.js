const linkedGrammarModules = [];

export async function linkGrammarModuleAsync(bytes, memory, table, hostFunctions, minAbi, maxAbi) {
  const module = await WebAssembly.compile(bytes);
  return linkGrammarModule(module, memory, table, hostFunctions, minAbi, maxAbi);
}

export function linkGrammarModuleSync(bytes, memory, table, hostFunctions, minAbi, maxAbi) {
  return linkGrammarModule(new WebAssembly.Module(bytes), memory, table, hostFunctions, minAbi, maxAbi);
}

function linkGrammarModule(module, memory, table, hostFunctions, minAbi, maxAbi) {
  const constructors = WebAssembly.Module.exports(module)
    .filter(({ name, kind }) => kind === "function" &&
      /^tree_sitter_\w+$/.test(name) && !name.includes("external_scanner_"));
  if (constructors.length !== 1) {
    throw new Error(`expected one Tree-sitter grammar constructor; found ${constructors.map(
      ({ name }) => name).join(", ") || "none"}`);
  }
  const source = constructors[0].name;
  const dylink = WebAssembly.Module.customSections(module, "dylink.0");
  if (dylink.length !== 1) throw new Error(`grammar ${source} has no unique dylink.0 section`);
  const info = readDylinkMemoryInfo(new Uint8Array(dylink[0]));

  const allocationSize = info.memorySize + 2 ** info.memoryAlignment - 1;
  if (!Number.isSafeInteger(allocationSize) || allocationSize > 0xffffffff) {
    throw new Error(`grammar ${source} requests too much static memory`);
  }
  const stackSize = 64 * 1024;
  const stackAllocationSize = stackSize + 15;
  const oldTableLength = table.length;
  const tableBase = alignUp(oldTableLength, info.tableAlignment);
  if (tableBase + info.tableSize > 0xffffffff) {
    throw new Error(`grammar ${source} requests too many table entries`);
  }
  const newTableLength = tableBase + info.tableSize;

  const dynamicImports = {
    memory,
    __indirect_function_table: table,
    __memory_base: null,
    __table_base: new WebAssembly.Global({ value: "i32" }, tableBase),
    __stack_pointer: null,
    __assert_fail: () => { throw new Error(`grammar ${source} assertion failed`); },
    abort: () => { throw new Error(`grammar ${source} called abort`); },
    proc_exit: () => { throw new Error(`grammar ${source} called proc_exit`); },
    __cxa_atexit: () => 0,
    args_get: () => 0,
    args_sizes_get: () => 0,
    emscripten_notify_memory_growth: () => {},
    tree_sitter_debug_message: () => {},
    ...hostFunctions,
  };
  for (const { module: namespace, name, kind } of WebAssembly.Module.imports(module)) {
    if (namespace !== "env" || !Object.prototype.hasOwnProperty.call(dynamicImports, name)) {
      throw new Error(`grammar ${source} has unsupported import ${namespace}.${name}`);
    }
    const value = dynamicImports[name];
    if ((kind === "function" && typeof value !== "function") ||
        (kind === "memory" && !(value instanceof WebAssembly.Memory)) ||
        (kind === "table" && !(value instanceof WebAssembly.Table)) ||
        (kind === "global" && name !== "__memory_base" &&
         name !== "__stack_pointer" &&
         !(value instanceof WebAssembly.Global)) ||
        !["function", "memory", "table", "global"].includes(kind)) {
      throw new Error(`grammar ${source} has incompatible import ${namespace}.${name}`);
    }
  }

  const allocation = hostFunctions.calloc(1, allocationSize) >>> 0;
  if (!allocation && allocationSize) throw new Error(`failed to allocate memory for ${source}`);
  let stackAllocation = 0;
  try {
    const memoryBase = alignUp(allocation, info.memoryAlignment);
    stackAllocation = hostFunctions.calloc(1, stackAllocationSize) >>> 0;
    if (!stackAllocation) throw new Error(`failed to allocate a stack for ${source}`);
    const stackTop = Math.floor((stackAllocation + stackAllocationSize) / 16) * 16;
    if (stackTop > 0xffffffff || memoryBase + info.memorySize > memory.buffer.byteLength ||
        stackTop > memory.buffer.byteLength) {
      throw new Error(`grammar ${source} allocations exceed host memory`);
    }

    dynamicImports.__memory_base = new WebAssembly.Global({ value: "i32" }, memoryBase);
    dynamicImports.__stack_pointer = new WebAssembly.Global(
      { value: "i32", mutable: true }, stackTop);
    table.grow(newTableLength - oldTableLength);

    const instance = new WebAssembly.Instance(module, { env: dynamicImports });
    instance.exports.__wasm_apply_data_relocs?.();
    instance.exports._initialize?.();
    instance.exports.__wasm_call_ctors?.();
    const rawAddress = instance.exports[source]();
    if (!Number.isInteger(rawAddress)) {
      throw new Error(`grammar ${source} returned an invalid language address`);
    }
    const address = rawAddress >>> 0;
    if (!address || address + 4 > memory.buffer.byteLength) {
      throw new Error(`grammar ${source} returned an out-of-bounds language address`);
    }
    const abi = new DataView(memory.buffer).getUint32(address, true);
    if (abi < minAbi || abi > maxAbi) {
      throw new Error(`grammar ${source} has incompatible ABI version ${abi}`);
    }
    // Language pointers and scanner function indices remain live for the page lifetime.
    linkedGrammarModules.push({ module, instance, allocation, stackAllocation });
    return address;
  } catch (error) {
    // Instantiation may have initialized table entries before a later step
    // failed. Clear them before releasing the memory their functions use.
    for (let index = oldTableLength; index < newTableLength && index < table.length; index++) {
      table.set(index, null);
    }
    if (stackAllocation) hostFunctions.free(stackAllocation);
    if (allocation) hostFunctions.free(allocation);
    throw error;
  }
}

function readDylinkMemoryInfo(bytes) {
  const reader = new LebReader(bytes);
  while (reader.offset < bytes.length) {
    const kind = reader.unsigned();
    const size = reader.unsigned();
    const end = reader.offset + size;
    if (end > bytes.length) throw new Error("dylink subsection exceeds its section");
    if (kind === 1) {
      const memorySize = reader.unsigned();
      const memoryAlignment = reader.unsigned();
      const tableSize = reader.unsigned();
      const tableAlignment = reader.unsigned();
      if (reader.offset !== end || memoryAlignment > 30 || tableAlignment > 30) {
        throw new Error("invalid dylink memory requirements");
      }
      return { memorySize, memoryAlignment, tableSize, tableAlignment };
    }
    reader.offset = end;
  }
  throw new Error("dylink.0 has no memory-info subsection");
}

function alignUp(value, exponent) {
  const alignment = 2 ** exponent;
  const aligned = Math.ceil(value / alignment) * alignment;
  if (!Number.isSafeInteger(aligned) || aligned > 0xffffffff) {
    throw new Error("grammar allocation alignment overflow");
  }
  return aligned;
}

class LebReader {
  constructor(bytes) { this.bytes = bytes; this.offset = 0; }
  unsigned() {
    let result = 0, shift = 0;
    for (;;) {
      if (this.offset >= this.bytes.length) throw new Error("truncated dylink.0");
      const byte = this.bytes[this.offset++];
      result += (byte & 0x7f) * 2 ** shift;
      if (result > 0xffffffff) throw new Error("dylink integer exceeds u32");
      if (!(byte & 0x80)) return result;
      shift += 7;
      if (shift > 35) throw new Error("invalid dylink integer");
    }
  }
}
