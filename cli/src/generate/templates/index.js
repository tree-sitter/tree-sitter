try {
  module.exports = require("./build/Release/tree_sitter_PARSER_NAME_binding");
} catch (error) {
  if (error.code !== 'MODULE_NOT_FOUND')
    throw error
  else try {
    module.exports = require("./build/Debug/tree_sitter_PARSER_NAME_binding");
  } catch (error2) {
    if (error2.code === 'MODULE_NOT_FOUND')
      throw error
    throw error2
  }
}

try {
  module.exports.nodeTypeInfo = require("./src/node-types.json");
} catch (_) {}
