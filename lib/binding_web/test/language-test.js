const { assert } = require("chai");
let JavaScript;

describe("Language", () => {
  before(async () => ({ JavaScript } = await require("./helper")));

  describe(".fieldIdForName, .fieldNameForId", () => {
    it("converts between the string and integer representations of fields", () => {
      const nameId = JavaScript.fieldIdForName("name");
      const bodyId = JavaScript.fieldIdForName("body");

      assert.isBelow(nameId, JavaScript.fieldCount);
      assert.isBelow(bodyId, JavaScript.fieldCount);
      assert.equal("name", JavaScript.fieldNameForId(nameId));
      assert.equal("body", JavaScript.fieldNameForId(bodyId));
    });

    it("handles invalid inputs", () => {
      assert.equal(null, JavaScript.fieldIdForName("namezzz"));
      assert.equal(null, JavaScript.fieldNameForId(-1));
      assert.equal(null, JavaScript.fieldNameForId(10000));
    });
  });

  describe(".idForNodeType, .nodeTypeForId, .nodeTypeIsNamed", () => {
    it("converts between the string and integer representations of a node type", () => {
      const exportStatementId = JavaScript.idForNodeType("export_statement", true);
      const starId = JavaScript.idForNodeType("*", false);

      assert.isBelow(exportStatementId, JavaScript.nodeTypeCount);
      assert.isBelow(starId, JavaScript.nodeTypeCount);
      assert.equal(true, JavaScript.nodeTypeIsNamed(exportStatementId))
      assert.equal("export_statement", JavaScript.nodeTypeForId(exportStatementId))
      assert.equal(false, JavaScript.nodeTypeIsNamed(starId))
      assert.equal("*", JavaScript.nodeTypeForId(starId))
    });

    it("handles invalid inputs", () => {
      assert.equal(null, JavaScript.nodeTypeForId(-1));
      assert.equal(null, JavaScript.nodeTypeForId(10000));
      assert.equal(null, JavaScript.idForNodeType("export_statement", false));
    });
  });
});
