module.exports = {
  environments: {
    emscripten: {
      globals: {
        getValue: false,
        setValue: false,
        Module: false,
        AsciiToString: false,
        UTF8ToString: false,
        stringToUTF16: false,
        lengthBytesUTF8: false,
        stringToUTF8: false,
        loadWebAssemblyModule: false,
        mergeInto: false,
        LibraryManager: false
      }
    }
  }
}
