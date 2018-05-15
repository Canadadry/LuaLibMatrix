package.cpath = "../build/?.so"
package.cpath = "./build/?.so"
hello = require "lua_matrix"

print(Matrix)
print(type(Matrix))

local value = Matrix.new(3,3,1)
print(value)
print(type(value))