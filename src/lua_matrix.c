#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "matrix.h"

Matrix* check_type(lua_State * l, int n)
{
    return *(Matrix **)luaL_checkudata(l, n, "MatrixeMetatableName");
}

int lua_matrix_new(lua_State * l)
{
    printf("matrix_constructor\n");

	const unsigned int rows    = luaL_checknumber (l, 1);
	const unsigned int columns = luaL_checknumber (l, 2);
	const double       values  = luaL_checknumber (l, 3);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_new(rows,columns,values);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}


int lua_matrix_free(lua_State * l)
{
    printf("destructor\n");
    Matrix* matrix = check_type(l, 1);
    matrix_delete(matrix);
    return 0;
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
    Matrix* ma = check_type(l, 1);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_copy(ma);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_transpose(lua_State * l)
{
    Matrix* ma = check_type(l, 1);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_transpose(ma);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_get(lua_State * l)
{
    Matrix* ma = check_type(l, 1);
    const unsigned int row    = luaL_checknumber (l, 2);
    const unsigned int column    = luaL_checknumber (l, 3);

    const double data = matrix_get(ma,row,column);
    lua_pushnumber(l, data);
    return 1;
}

int lua_matrix_set(lua_State * l)
{
    Matrix* ma = check_type(l, 1);
    const unsigned int row    = luaL_checknumber (l, 2);
    const unsigned int column    = luaL_checknumber (l, 3);
    const double value    = luaL_checknumber (l, 4);
    
    matrix_set(ma,row,column,value);
    
    return 0;
}

int lua_matrix_add(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_add(m1,m2);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_addnum(lua_State * l)
{
    Matrix* m1   = check_type(l, 1);
    double value = luaL_checknumber (l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_addnum(m1,value);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_sub(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_sub(m1,m2);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_mul(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_mul(m1,m2);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_mulnum(lua_State * l)
{
    Matrix* m1   = check_type(l, 1);
    double value = luaL_checknumber (l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_mulnum(m1,value);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_hadamard_mul(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));
    *udata = matrix_hadamard_mul(m1,m2);
    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;
}

int lua_matrix_is_equal(lua_State * l)
{
    Matrix* m1 = check_type(l, 1);
    Matrix* m2 = check_type(l, 2);

    unsigned char out = matrix_is_equal(m1,m2);
    lua_pushboolean(l, out);
    return 1;
}

int lua_matrix_get_ref_counter(lua_State * l)
{
    lua_pushnumber(l, matrix_get_ref_counter());
    return 1;
}

static const struct luaL_Reg functions [] = {
    { "new"         , lua_matrix_new },
    { "__gc"        , lua_matrix_free      },
    { "__tostring"  , lua_matrix_print  },
    { "copy"  , lua_matrix_copy  },
    { "transpose"  , lua_matrix_transpose  },
    { "get"  , lua_matrix_get  },
    { "set"  , lua_matrix_set  },
    { "add"  , lua_matrix_add  },
    { "addnum"  , lua_matrix_addnum  },
    { "sub"  , lua_matrix_sub  },
    { "mul"  , lua_matrix_mul  },
    { "mulnum"  , lua_matrix_mulnum  },
    { "hadamard_mul"  , lua_matrix_hadamard_mul  },
    { "is_equal"  , lua_matrix_is_equal  },
    { "count", lua_matrix_get_ref_counter},
    {NULL, NULL}
};


int luaopen_lua_matrix(lua_State *l) {
	printf("luaopen_lua_matrix\n");

    luaL_newmetatable(l, "MatrixeMetatableName" );
    luaL_setfuncs(l, functions,0);           
    lua_pushvalue(l, -1);                      
    lua_setfield(l, -1, "__index");          
    lua_setglobal(l, "Matrix");          

    return 1;
}


