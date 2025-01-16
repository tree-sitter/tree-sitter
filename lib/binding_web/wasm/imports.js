mergeInto(LibraryManager.library, {
  tree_sitter_parse_callback(
    inputBufferAddress,
    index,
    row,
    column,
    lengthAddress,
  ) {
    const INPUT_BUFFER_SIZE = 10 * 1024;
    const string = currentParseCallback(index, { row, column });
    if (typeof string === 'string') {
      setValue(lengthAddress, string.length, 'i32');
      stringToUTF16(string, inputBufferAddress, INPUT_BUFFER_SIZE);
    } else {
      setValue(lengthAddress, 0, 'i32');
    }
  },

  tree_sitter_log_callback(isLexMessage, messageAddress) {
    if (currentLogCallback) {
      const message = UTF8ToString(messageAddress);
      currentLogCallback(message, isLexMessage !== 0);
    }
  },

  tree_sitter_progress_callback(currentOffset) {
    if (currentProgressCallback) {
      return currentProgressCallback({ currentOffset });
    }
    return false;
  },

  tree_sitter_query_progress_callback(currentOffset) {
    if (currentQueryProgressCallback) {
      return currentQueryProgressCallback({ currentOffset });
    }
    return false;
  },
});
