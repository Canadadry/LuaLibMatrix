#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "matrix.h"

int matrinx_constructor(lua_State * l)
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

Matrix* check_type(lua_State * l, int n)
{
    return *(Matrix **)luaL_checkudata(l, n, "MatrixeMetatableName");
}

int destructor(lua_State * l)
{
    printf("destructor\n");
    Matrix* matrix = check_type(l, 1);
    matrix_delete(matrix);
    return 0;
}

int print_type(lua_State * l)
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

static const struct luaL_Reg functions [] = {
    { "new"         , matrinx_constructor },
    { "__gc"        , destructor      },
    { "__tostring"  , print_type  },
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


