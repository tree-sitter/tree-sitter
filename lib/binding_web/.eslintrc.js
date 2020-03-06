module.exports = {
  "env": { "browser": true, "es6": true, "node": true },
  "extends": ["eslint:recommended", "plugin:prettier/recommended"],
  "parserOptions": {
    "ecmaVersion": 2018,
    "sourceType": "module"
  },
  "overrides": [
    {
      "files": ["src/ts/**/*.ts"],
      "env": { "browser": true, "es6": true, "node": true },
      "extends": [
        "eslint:recommended",
        "plugin:@typescript-eslint/eslint-recommended",
        "plugin:@typescript-eslint/recommended",
        "prettier/@typescript-eslint",
        "plugin:prettier/recommended"
      ],
      "parser": "@typescript-eslint/parser",
      "parserOptions": {
        "ecmaVersion": 2018,
        "sourceType": "module",
        "project": "./tsconfig.json"
      },
      "plugins": ["@typescript-eslint"],
    }
  ]
};
