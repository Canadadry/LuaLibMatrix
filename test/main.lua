package.cpath = "../build/?.so"
hello = require "lua_matrix"

print(Matrix)
print(type(Matrix))
for j=1,10000 do
	for i=1,10 do

		local input = Matrix.new(2,1,1)
		local target = Matrix.new(1,1,1)

		local layer_h_o = Matrix.new(1,4,0)
		local bias_o    = Matrix.new(1,1,0)

		local layer_i_h = Matrix.new(4,2,0)
		local bias_h    = Matrix.new(4,1,0)

		local output = Matrix.new(1,1,1)
		local output_err = target:sub(output)
		local hiddent_err = layer_h_o:transpose():mul(output_err)
		local gradient = output:copy()
		gradient:map(function (i,j,x) return x*(1-x) end)
		gradient = gradient:hadamard_mul(output_err):mulnum(0.1)

		bias_o = bias_o:add(gradient)


    	local last_hidden = layer_i_h:mul(input):add(bias_h)
		local hidden_t = last_hidden:transpose()
		local weight_ho_delta = gradient:mul(hidden_t)

		layer_h_o = layer_h_o:add(weight_ho_delta)

		-- hidden gradient
		local hidden_gradient = last_hidden:copy()
		hidden_gradient:map(function (i,j,x) return x*(1-x) end)
		hidden_gradient = hidden_gradient:hadamard_mul(hiddent_err):mulnum(0.1)

		bias_h = bias_h:add(hidden_gradient)

		local input_t = input:transpose()
		local weight_ih_delta = hidden_gradient:mul(input_t)

		layer_i_h = layer_i_h:add(weight_ih_delta)
	end

	print("Matrix forget : ".. Matrix.count());
	-- collectgarbage()
end

-- local m = Matrix.new(2,4,1)

-- local count = 0
-- for i=0,1 do
-- 	for j=0,3 do
-- 		m:set(i,j,count)
-- 		count= count + 1
-- 	end
-- end
-- m:set(0,3,1)
-- print(m:get(1,3))

-- local m2 = m:transpose()
-- print(m)
-- print(m2)

-- m = Matrix.new(2,4,1)

-- local count = 0
-- for i=0,1 do
-- 	for j=0,3 do
-- 		m:set(i,j,count)
-- 		count= count + 1
-- 	end
-- end

-- m2 = m:add(m)


-- print(m)
-- print(m2)

-- 	-- 1,2,3   * 1,4   =   14,32
-- 	-- 4,5,6     2,5       32,77
-- 	--           3,6


-- m = Matrix.new(2,3,1)

-- count = 0
-- Table = {}
-- function Table.test_set( i,j,v )
-- 	count = count + 1
-- 	return count
-- end

-- print('test map')
-- m:map(Table.test_set)

-- m:map(function (i,j,v) return math.sin(v) end)

-- m2 = m:transpose()


-- print(m)
-- print(m2)

-- print(m:mul(m2))

-- print(m:encode())
-- local r,c,d = m:encode()

-- m3 = Matrix.copy(Matrix.decode(r,c,d))
-- print(m3)

-- print("Matrix forget : ".. Matrix.count());
-- collectgarbage()
-- print("Matrix forget : ".. Matrix.count());
-- m = nil
-- m2 = nil
-- collectgarbage()
-- print("Matrix forget : ".. Matrix.count());




