-- Omega.lua

io.write("Loading omega.lua...\n")

package.path = package.path .. ";scripts/?.lua"

function max(first, second)
    return math.max(first, second)
end
