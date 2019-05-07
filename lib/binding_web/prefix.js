(function (root, factory) {
  if (typeof define === 'function' && define.amd) {
    define([], factory);
  } else if (typeof exports === 'object') {
    module.exports = factory();
    // module.exports.init();
    // delete module.exports.init;
  } else {
    window.TreeSitter = factory();
  }
}(this, function () {
