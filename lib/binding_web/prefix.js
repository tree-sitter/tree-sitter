var TreeSitter = function() {
  var initPromise;
  class Parser {
    constructor() {
      this.initialize();
    }

    initialize() {
      throw new Error("cannot construct a Parser before calling `init()`");
    }

    static init(moduleOptions) {
      if (initPromise) return initPromise;
      Module = { ...Module, ...moduleOptions };
      return initPromise = new Promise((resolveInitPromise) => {
