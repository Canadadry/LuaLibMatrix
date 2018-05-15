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
    return *(Matrix **)luaL_checkudata(l, n, "MatrixeMetatableName");
}

int lua_matrix_new(lua_State * l)
{
    //printf("matrix_constructor\n");

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
    //printf("destructor\n");
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
    if(*udata == 0 )
    {
        luaL_error(l,"error while adding matrix : size dont match");
    }
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
     if(*udata == 0 )
    {
        luaL_error(l,"error while substracting matrix : size dont match");
    }

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
    if(*udata == 0 )
    {
        luaL_error(l,"error while multiplying matrix : size dont match");
    }

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
    if(*udata == 0 )
    {
        luaL_error(l,"error while multiplying matrix : size dont match");
    }

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

int lua_encode(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    size_t b64_len = 0;
    unsigned char* out = base64_encode((const unsigned char *)m->data,matrix_data_size(m),&b64_len);

    lua_pushnumber(l, m->rows);
    lua_pushnumber(l, m->columns);
    lua_pushstring(l, (const char*)out);
    free(out);
    return 3;
}

int lua_decode(lua_State * l)
{
    double rows = luaL_checknumber (l, 1);
    double columns = luaL_checknumber (l, 2);
    const char* str = luaL_checkstring(l, 3);

    Matrix ** udata = (Matrix **)lua_newuserdata(l, sizeof(Matrix *));

    *udata  = malloc(sizeof(Matrix));
    (*udata)->rows    = rows;
    (*udata)->columns = columns;

    size_t converted_data = 0;

    (*udata)->data = (double*) base64_decode((const unsigned char *)str, strlen(str) ,&converted_data);

    if(matrix_data_size(*udata) != converted_data)
    {
        matrix_delete(*udata);
        luaL_error(l,"Error while decoding matrix data : data size not matching (row,col) provided\n");
    }

    luaL_getmetatable(l, "MatrixeMetatableName" );
    lua_setmetatable(l, -2);
    return 1;

}


int lua_map(lua_State * l)
{
    Matrix* m = check_type(l, 1);
    if(lua_gettop(l)== 2 && lua_isfunction(l, 2))
    {        
        int r = luaL_ref(l, LUA_REGISTRYINDEX);
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
    { "encode", lua_encode},
    { "decode", lua_decode},
    { "map", lua_map},
    { "columns", lua_columns},
    { "rows", lua_rows},

    {NULL, NULL}
};


int luaopen_lua_matrix(lua_State *l) {
	//printf("luaopen_lua_matrix\n");

    luaL_newmetatable(l, "MatrixeMetatableName" );
    luaL_setfuncs(l, functions,0);           
    lua_pushvalue(l, -1);                      
    lua_setfield(l, -1, "__index");          
    lua_setglobal(l, "Matrix");          

    return 1;
}


