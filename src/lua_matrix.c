#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "matrix.h"
#include "base64.h"

Matrix* check_type(lua_State * l, int n)
{
    return (Matrix *)luaL_checkudata(l, n, "MatrixeMetatableName");
}

int lua_matrix_new(lua_State * l)
{
	const unsigned int rows    = luaL_checknumber (l, 1);
	const unsigned int columns = luaL_checknumber (l, 2);
	const double       values  = luaL_checknumber (l, 3);

    Matrix m;
    m.rows = rows;
    m.columns = columns;

    void* udata = lua_newuserdata(l, sizeof(Matrix) + matrix_data_size(&m));
    matrix_init_with_pre_malloc(rows,columns,values,udata);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_print(lua_State * l)
{
    Matrix* ma = check_type(l, 1);
	const unsigned int maxSizeCell = 20;
	const unsigned int headerSize = 50;
	const unsigned int sizeRequiredToPrint = ma->rows*ma->columns*maxSizeCell+headerSize;

    char str[sizeRequiredToPrint];
    matrix_print(ma,str,sizeRequiredToPrint);
    lua_pushstring(l, str);
    return 1;
}

int lua_matrix_copy(lua_State * l)
{
    Matrix* in = check_type(l, 1);
    Matrix* out = check_type(l, 2);

    if (matrix_copy(in,out) == 0)
    {
        luaL_error(l,"error while copying matrix : size dont match");
    }
    return 0;
}

int lua_matrix_transpose(lua_State * l)
{
    Matrix* in = check_type(l, 1);
    Matrix* out = check_type(l, 2);

    if (matrix_transpose(in,out) == 0)
    {
        luaL_error(l,"error while transposing matrix : size dont match");
    }
    return 0;
}

int lua_matrix_add(lua_State * l)
{
    Matrix* in  = check_type(l, 1);
    Matrix* out = check_type(l, 2);

    if (matrix_add(in,out) == 0)
    {
        luaL_error(l,"error while adding matrix : size dont match");
    }
    return 0;
}

int lua_matrix_sub(lua_State * l)
{
    Matrix* in  = check_type(l, 1);
    Matrix* out = check_type(l, 2);

    if (matrix_sub(in,out) == 0)
    {
        luaL_error(l,"error while substracting matrix : size dont match");
    }
    return 0;
}

int lua_matrix_hadamard_mul(lua_State * l)
{
    Matrix* m1  = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    if (matrix_hadamard_mul(m1,m2) == 0)
    {
        luaL_error(l,"error while hadamard_mul matrix : size dont match");
    }
    return 0;
}

int lua_matrix_mulnum(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    const double value = luaL_checknumber (l, 2);

    matrix_mulnum(m,value);
    return 0;
}

int lua_matrix_mul(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);
    Matrix* out = check_type(l, 3);

    if ( matrix_mul(m1,m2,out) == 0)
    {
        luaL_error(l,"error while multiplying matrix : size dont match");
    }
    return 0;
}

int lua_columns(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    lua_pushnumber(l, m->columns);
    return 1;
}

int lua_rows(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    lua_pushnumber(l, m->rows);
    return 1;
}


int lua_map(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    if(lua_gettop(l)== 2 && lua_isfunction(l, 2))
    {        
        const int r = luaL_ref(l, LUA_REGISTRYINDEX);
        for (unsigned int i = 0; i < m->rows; i++)
        {   
            for (unsigned int j = 0; j < m->columns; j++)
            {
                lua_rawgeti(l, LUA_REGISTRYINDEX, r); 
                lua_pushnumber(l,i);
                lua_pushnumber(l,j);
                lua_pushnumber(l,m->data[j+i*m->columns]);
                lua_call(l, 3, 1);
                m->data[j+i*m->columns] = luaL_checknumber(l, -1);
                lua_pop(l, 1); 
            }
        }
        luaL_unref(l, LUA_REGISTRYINDEX, r);
    }
    return 0;
}



static const struct luaL_Reg functions [] = {
    { "new"         , lua_matrix_new },
    { "copy"        , lua_matrix_copy  },
    { "transpose"   , lua_matrix_transpose  },
    { "add"         , lua_matrix_add  },
    { "sub"         , lua_matrix_sub  },
    { "mul"         , lua_matrix_mul  },
    { "hadamard_mul", lua_matrix_hadamard_mul },
    { "mulnum"      , lua_matrix_mulnum},
    { "map"         , lua_map         },    
    { "columns"     , lua_columns},
    { "rows"        , lua_rows},
    { "__tostring"  , lua_matrix_print },
    {NULL, NULL}
};


int luaopen_lua_matrix(lua_State *l) 
{
    luaL_newmetatable(l, "MatrixeMetatableName" );
    luaL_setfuncs(l, functions,0);           
    lua_pushvalue(l, -1);                      
    lua_setfield(l, -1, "__index");          
    lua_setglobal(l, "Matrix");          

    return 1;
}


