        for (const name of Object.getOwnPropertyNames(ParserImpl.prototype)) {
          Object.defineProperty(Parser.prototype, name, {
            value: ParserImpl.prototype[name],
            enumerable: false,
            writable: false,
          })
        }

        Parser.Language = Language;
        Module.onRuntimeInitialized = () => {
          ParserImpl.init();
          resolveInitPromise();
        };
      });
    }
  }

  return Parser;
}();

if (typeof exports === 'object') {
  module.exports = TreeSitter;
}
