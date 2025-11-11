# `tree-sitter version`

The `version` command upgrades the version of your grammar.

```bash
tree-sitter version <VERSION> # Aliases: publish
```

This will update the version in several files, if they exist:

* tree-sitter.json
* Cargo.toml
* Cargo.lock
* package.json
* package-lock.json
* Makefile
* CMakeLists.txt
* pyproject.toml

Alternative forms can use the version in `tree-sitter.json` to bump automatically:

```bash
tree-sitter version --bump patch # patch bump
tree-sitter version --bump minor # minor bump
tree-sitter version --bump major # major bump
```

As a grammar author, you should keep the version of your grammar in sync across
different bindings. However, doing so manually is error-prone and tedious, so
this command takes care of the burden. If you are using a version control system,
it is recommended to commit the changes made by this command, and to tag the
commit with the new version.

To print the current version without bumping it, use:

```bash
tree-sitter version
```

Note that some of the binding updates require access to external tooling:

* Updating Cargo.toml and Cargo.lock bindings requires that `cargo` is installed.
* Updating package-lock.json requires that `npm` is installed.

## Options

### `-p/--grammar-path <PATH>`

The path to the directory containing the grammar.

### `--bump`

Automatically bump the version. Possible values are:

- `patch`: Bump the patch version.
- `minor`: Bump the minor version.
- `major`: Bump the major version.
