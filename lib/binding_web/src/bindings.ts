import createModule, { type MainModule } from '../lib/tree-sitter';

export let Module: MainModule | null = null;

export async function initializeBinding(moduleOptions?: EmscriptenModule): Promise<MainModule> {
  if (!Module) {
    Module = await createModule(moduleOptions);
  }
  return Module;
}

export function checkModule(): boolean {
  return !!Module;
}
