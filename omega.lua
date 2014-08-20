-- Omega.lua

io.write("Loading omega.lua...\n")

package.path = package.path .. ";scripts/?.lua"

require("log")
require("player")

function max(first, second)
    return math.max(first, second)
end

function min(first, second)
    return math.min(first, second)
end
