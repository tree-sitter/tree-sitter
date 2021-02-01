const { assert } = require("chai");
let JavaScript;

describe("Language", () => {
  before(async () => ({ JavaScript } = await require("./helper")));

  describe(".fieldCount", () => {
    it("returns a number", () => {
      assert.equal(34, JavaScript.fieldCount);
    });
  });

  describe(".fieldIdForName", () => {
    it("returns null, if not defined", () => {
      const fieldName = "nonExistentFieldName";
      assert.equal(null, JavaScript.fieldIdForName(fieldName));
    });

    it("returns a number, if defined", () => {
      const fieldName = "decorator";
      assert.equal(12, JavaScript.fieldIdForName(fieldName));
    });
  });

  describe(".fieldNameForId", () => {
    it("returns null, if not defined", () => {
      const fieldId = -1;
      assert.equal(null, JavaScript.fieldNameForId(fieldId));
    });

    it("returns a string, if defined", () => {
      const fieldId = 12;
      assert.equal("decorator", JavaScript.fieldNameForId(fieldId));
    });
  });

  describe(".idForNodeType", () => {
    it("returns a number", () => {
      const type = "export_statement";
      const named = true;
      assert.equal(125, JavaScript.idForNodeType(type, named));
    });
  });

  describe(".nodeTypeCount", () => {
    it("returns a number", () => {
      assert.equal(239, JavaScript.nodeTypeCount);
    });
  });

  describe(".nodeTypeForId", () => {
    it("returns null, if not defined", () => {
      const typeId = -1;
      assert.equal(null, JavaScript.nodeTypeForId(typeId));
    });

    it("returns a string, if not defined", () => {
      const typeId = 125;
      assert.equal("export_statement", JavaScript.nodeTypeForId(typeId));
    });
  });

  describe(".nodeTypeIsNamed", () => {
    it("returns false, if node type is not named", () => {
      const typeId = 4;
      assert.equal("*", JavaScript.nodeTypeForId(typeId));
      assert.equal(false, JavaScript.nodeTypeIsNamed(typeId));
    });

    it("returns true, if node type is named", () => {
      const typeId = 125;
      assert.equal("export_statement", JavaScript.nodeTypeForId(typeId));
      assert.equal(true, JavaScript.nodeTypeIsNamed(typeId));
    });
  });

  describe(".nodeTypeIsVisible", () => {
    it("returns false, if node type is not visible", () => {
      let typeId;
      typeId = 100;
      assert.equal(false, JavaScript.nodeTypeIsVisible(typeId));
      typeId = 102;
      assert.equal(false, JavaScript.nodeTypeIsVisible(typeId));
    });

    it("returns true, if node type is visible", () => {
      const typeId = 101;
      assert.equal(true, JavaScript.nodeTypeIsVisible(typeId));
    });
  });

  describe(".version", () => {
    it("returns a number", () => {
      assert.equal(12, JavaScript.version);
    });
  });
});
