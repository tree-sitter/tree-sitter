local is_file = vim.fn.filereadable

local _cache = {}

vim.treesitter.query.add_directive("set-language-from-grammar!", function(_, _, bufnr, _, metadata)
    ---@cast bufnr integer
    local test_dir = vim.fs.find("test", {
        upward = true, type = "directory", limit = 1,
        path = vim.fs.dirname(vim.api.nvim_buf_get_name(bufnr))
    })[1]
    if test_dir == nil then return end
    if _cache[test_dir] ~= nil then
        metadata["injection.language"] = _cache[test_dir]
        return
    end
    local root_dir = vim.fs.dirname(test_dir --[[@as string]])
    local grammar_json = vim.fs.joinpath(root_dir, "src", "grammar.json")
    local package_json = vim.fs.joinpath(root_dir, "package.json")
    -- look for the path in package.json if src/grammar.json is not found
    if is_file(grammar_json) == 0 and is_file(package_json) == 1 then
        local file = assert(io.open(package_json))
        local data = vim.json.decode(file:read("*a"))
        local parser = (data["tree-sitter"] or {})[1]
        if parser then
            local path = "%s/%s/src/grammar.json"
            grammar_json = vim.fs.normalize(
                path:format(root_dir, parser["path"] or "")
            )
        end
        file:close()
    end
    if is_file(grammar_json) == 1 then
        local file = assert(io.open(grammar_json))
        local _, name = file:read("l", "l")
        metadata["injection.language"] = name:sub(12, #name - 2)
        _cache[test_dir] = metadata["injection.language"]
        file:close()
    end
end, {})
