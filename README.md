# LuaLibMatrix

Matrix computation un C for lua

This lua lib allow you to do basic matrix computation like multiplication, addition, transposition. 

# build

You need to have lua install in the default directory, it may be required to edit the make file if you have not build it from source. 

Just run make

```
make
```

It will also run the test 

# run

Here an example of usage


```
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

local count = 1
for i=0,1 do
	for j=0,2 do
		m:set(i,j,count)
		count= count + 1
	end
end

m2 = m:transpose();


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

```

# Function implemented

* new : a new matrix is returned
* __gc : free matrix, called by garbage collecting
* __tostring :  to allow `print(matrix)`
* copy : to duplicate a matrix
* transpose : transpose the matrix into a new one. current matrix is not changed
* get : get the value of one cell referenced by its row and column ( 0index value)
* set : set the value of one cell
* add :  add two matrix, a new one is create with result. Current matrix are not changed
* addnum : add one numbre to every cell of a matrix. a new one is create with result. Current matrix is not changed
* sub : sub two matrix, a new one is create with result. Current matrix are not changed
* mul :  classic matrix multiplication, be carreful with row col matching, a new one is create with result. Current matrix are not changed
* mulnum :  multiply one numbre to every cell of a matrix. a new one is create with result. Current matrix is not changed
* hadamard_mul : a cell by cell matrix multiplication
* is_equal : return a boolean wether the two matrix are equal
* count :  count of many matrix are still in memory
* encode : return row, col and a base64 string of matrix data
* decode : provide row, col and a base64 string of matrix data to load matrix


