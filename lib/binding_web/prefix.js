var TreeSitter = function() {
  var initPromise;
  var document = typeof window == 'object'
    ? {currentScript: window.document.currentScript}
    : null;

  class Parser {
    constructor() {
      this.initialize();
    }

    initialize() {
      throw new Error("cannot construct a Parser before calling `init()`");
    }

    static init(moduleOptions) {
      if (initPromise) return initPromise;
      Module = Object.assign({}, Module, moduleOptions);
      return initPromise = new Promise((resolveInitPromise) => {
