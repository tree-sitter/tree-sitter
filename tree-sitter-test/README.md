# tree-sitter-test

[![CI][ci]](https://github.com/tree-sitter-grammars/tree-sitter-test/actions/workflows/ci.yml)
[![discord][discord]](https://discord.gg/w7nTvsVJhm)
[![matrix][matrix]](https://matrix.to/#/#tree-sitter-chat:matrix.org)
<!-- TODO: uncomment these before publishing -->
<!-- [![npm][npm]](https://www.npmjs.com/package/tree-sitter-test) -->
<!-- [![crates][crates]](https://crates.io/crates/tree-sitter-test) -->
<!-- [![pypi][pypi]](https://pypi.org/project/tree-sitter-test/) -->


A tree-sitter parser for corpus test files.

## References

- [Command: test](https://tree-sitter.github.io/tree-sitter/creating-parsers#command-test)
- [Constant `std::env::consts::OS`](https://doc.rust-lang.org/std/env/consts/constant.OS.html)

## Usage

This can be used as a standalone plugin in Neovim, without nvim-treesitter.<br>
Here's how you can install it using [lazy.nvim](https://github.com/folke/lazy.nvim):

```lua
{
    "tree-sitter-grammars/tree-sitter-test",
    -- compile on your own on Windows
    build = "make parser/test.so",
    ft = "test",
    init = function()
        -- toggle full-width rules for test separators
        vim.g.tstest_fullwidth_rules = false
        -- set the highlight group of the rules
        vim.g.tstest_rule_hlgroup = "FoldColumn"
    end
}
```

[ci]: https://img.shields.io/github/actions/workflow/status/tree-sitter-grammars/tree-sitter-test/ci.yml?logo=github&label=CI
[discord]: https://img.shields.io/discord/1063097320771698699?logo=discord&label=discord
[matrix]: https://img.shields.io/matrix/tree-sitter-chat%3Amatrix.org?logo=matrix&label=matrix
[npm]: https://img.shields.io/npm/v/tree-sitter-test?logo=npm
[crates]: https://img.shields.io/crates/v/tree-sitter-test?logo=rust
[pypi]: https://img.shields.io/pypi/v/tree-sitter-test?logo=pypi&logoColor=ffd242
