vim.treesitter.start()

vim.wo.foldmethod = "expr"
vim.wo.foldexpr = "v:lua.vim.treesitter.foldexpr()"

local conceals = vim.treesitter.query.parse("test", [[
(test (separator) @dashes)

(header . (separator) @equals.begin)

(header (separator) @equals.end .)
]])

---@param ns integer
---@param root TSNode
---@param start integer
---@param stop integer
local function set_rules(ns, root, start, stop)
    for id, node, _ in conceals:iter_captures(root, 0, start, stop) do
        local name = conceals.captures[id]
        local row, col, _, _ = node:range()
        if name == "dashes" then
            vim.api.nvim_buf_set_extmark(0, ns, row, col, {
                virt_text_pos = "overlay",
                virt_text_hide = true,
                virt_text = {{
                    string.rep("-", vim.o.columns),
                    vim.g.tstest_rule_hlgroup or "FoldColumn"
                }}
            })
        else
            vim.api.nvim_buf_set_extmark(0, ns, row, col, {
                virt_text_pos = "overlay",
                virt_text_hide = true,
                virt_text = {{
                    string.rep("=", vim.o.columns),
                    vim.g.tstest_rule_hlgroup or "FoldColumn"
                }}
            })
        end
    end
end

if vim.g.tstest_fullwidth_rules then
    local ns = vim.api.nvim_create_namespace("tstest-rules")
    local parser = vim.treesitter.get_parser()
    set_rules(ns, parser:parse()[1]:root(), 0, 0)
    parser:register_cbs({
        ---@param ranges Range6[]
        ---@param tree TSTree
        on_changedtree = function(ranges, tree)
            ---@param range Range6
            vim.iter(ranges):each(function(range)
                vim.api.nvim_buf_clear_namespace(0, ns, range[1], range[3])
                set_rules(ns, tree:root(), range[1], range[3])
            end)
        end
    }, false)
end
