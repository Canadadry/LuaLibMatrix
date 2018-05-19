package.cpath = "../build/?.so"
require "lua_matrix"

local input           = Matrix.new(2,1,1)
-- 
local layer_i_h       = Matrix.new(4,2,0)
local bias_h          = Matrix.new(4,1,0)
-- 
local output          = Matrix.new(1,1,1)
local gradient        = Matrix.new(1,1,1)
-- 
local last_hidden     = Matrix.new(4,1,0)
local hidden_t        = Matrix.new(1,4,0)
local weight_ho_delta = Matrix.new(1,4,0)

for j=1,20000 do
	 for i=1,100 do
-- 

-- 
    	Matrix.mul(layer_i_h,input,last_hidden)
    	Matrix.add(last_hidden,bias_h)
		Matrix.transpose(last_hidden,hidden_t)
		Matrix.mul(gradient,hidden_t,weight_ho_delta)
	end
end


