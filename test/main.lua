package.cpath = "../build/?.so"
package.cpath = "./build/?.so"
hello = require "lua_matrix"

print(Matrix)
print(type(Matrix))

local m = Matrix.new(2,4,1)

local count = 0
for i=0,1 do
	for j=0,3 do
		m:set(i,j,count)
		count= count + 1
	end
end
m:set(0,3,1)
print(m:get(1,3))

local m2 = m:transpose()
print(m)
print(m2)

m = Matrix.new(2,4,1)

local count = 0
for i=0,1 do
	for j=0,3 do
		m:set(i,j,count)
		count= count + 1
	end
end

m2 = m:add(m)


print(m)
print(m2)

	-- 1,2,3   * 1,4   =   14,32
	-- 4,5,6     2,5       32,77
	--           3,6


m = Matrix.new(2,3,1)

count = 0
Table = {}
function Table.test_set( i,j,v )
	count = count + 1
	return count
end

print('test map')
m:map(Table.test_set)

m:map(function (i,j,v) return math.sin(v) end)

m2 = m:transpose()


print(m)
print(m2)

print(m:mul(m2))

print(m:encode())
local r,c,d = m:encode()

m3 = Matrix.copy(Matrix.decode(r,c,d))
print(m3)

print("Matrix forget : ".. Matrix.count());
collectgarbage()
print("Matrix forget : ".. Matrix.count());
m = nil
m2 = nil
collectgarbage()
print("Matrix forget : ".. Matrix.count());




