let modules = {}

class CJSModule {
  constructor(id) {
    this.id = id
    this.exports = {}
    this._loaded = false
  }

  load() {
    const __file = this.id
    const contents = std.loadFile(__file)

    if (__file.endsWith(".json")) {
      this.exports = JSON.parse(contents)
      this._loaded = true
      return true
    }

    const __dir = _basename(this.id)
    const _require = require

    const ctx = { exports: {} }
    Object.seal(ctx) // Prevents modifications to exports object

    const scriptTemplate = `(function(exports, require, module, __filename, __dirname) { ${contents} })(ctx.exports, _require, ctx, __file, __dir)`

    try {
      eval(scriptTemplate)
      this.exports = ctx.exports
      this._loaded = true
      return true
    } catch (error) {
      return error
    }
  }
}

function _basename(path) {
  const idx = path.lastIndexOf('/')
  return idx === -1 ? path : path.substring(0, idx)
}

function _loadModule(id) {
  if (modules[id]) {
    return modules[id]
  }

  const module = new CJSModule(id)
  modules[id] = module

  const result = module.load()
  if (result !== true) {
    throw result
  }

  return module
}

function _lookupModule(path) {
  const fstat = _statPath(path)
  if (fstat.errno === 0 && fstat.isFile) {
    return fstat.resolved
  }

  if (fstat.isDir) {
    // Try package.json main field
    const packagePath = `${path}/package.json`
    const packageStat = _statPath(packagePath)
    let mainFile;
    if (packageStat.errno === 0 && packageStat.isFile) {
      const pkg = JSON.parse(std.loadFile(packagePath))
      mainFile = pkg.main || 'index.js'
      const mainFilePath = `${path}/${mainFile}`
      const mainFileStat = _statPath(mainFilePath)
      if (mainFileStat.errno === 0 && mainFileStat.isFile) {
        return mainFileStat.resolved
      }
    }

    // Fallback to index.js if no package.json or main field
    const indexPath = `${path}/index.js`
    const indexStat = _statPath(indexPath)
    if (indexStat.errno === 0 && indexStat.isFile) {
      return indexStat.resolved
    }
  }

  throw new Error(`Module not found: ${path}`)
}

globalThis.require = function (path) {
  const modulePath = _lookupModule(path)
  return _loadModule(modulePath).exports
}

globalThis.console = {
  log(...v) {
    try {
      const output = v.map(x => {
        try {
          return typeof x === 'object' ? JSON.stringify(x) : String(x);
        } catch (e) {
          return '[non-stringifiable value]';
        }
      }).join(' ');
      globalThis.__print(output);
    } catch (e) {
      globalThis.__print('Error in console.log: ' + e.message);
    }
  },

  warn(...v) {
    try {
      const output = v.map(x => {
        try {
          return typeof x === 'object' ? JSON.stringify(x) : String(x);
        } catch (e) {
          return '[non-stringifiable value]';
        }
      }).join(' ');
      globalThis.__warn(output);
    } catch (e) {
      globalThis.__warn('Error in console.warn: ' + e.message);
    }
  },

  error(...v) {
    try {
      const output = v.map(x => {
        try {
          return typeof x === 'object' ? JSON.stringify(x) : String(x);
        } catch (e) {
          return '[non-stringifiable value]';
        }
      }).join(' ');
      globalThis.__error(output);
    } catch (e) {
      globalThis.__error('Error in console.error: ' + e.message);
    }
  }
}
