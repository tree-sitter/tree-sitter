module.exports = {
  env: {
    browser: true,
    es6: true,
    node: true,
    amd: true,
    "emscripten/emscripten": true
  },
  extends: "eslint:recommended",
  plugins: ["emscripten"],
  overrides: [
    {
      files: ['test/**/*.js'],
      env: {
        mocha: true
      },
      parserOptions: {
        ecmaVersion: 2018,
      }
    }
  ]
}
