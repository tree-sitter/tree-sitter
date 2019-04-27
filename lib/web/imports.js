mergeInto(LibraryManager.library, {
  tree_sitter_parse_callback: function(
    inputBufferAddress,
    index,
    row,
    column,
    lengthAddress
  ) {
    var INPUT_BUFFER_SIZE = 10 * 1024;
    var string = currentParseCallback(index, {row: row, column: column});
    if (typeof string === 'string') {
      setValue(lengthAddress, string.length, 'i32');
      stringToUTF16(string, inputBufferAddress, INPUT_BUFFER_SIZE);
    } else {
      setValue(lengthAddress, 0, 'i32');
    }
  },

  tree_sitter_log_callback: function(_payload, isLexMessage, messageAddress) {
    if (currentLogCallback) {
      const message = UTF8ToString(messageAddress);
      currentLogCallback(message, isLexMessage !== 0);
    }
  }
});
