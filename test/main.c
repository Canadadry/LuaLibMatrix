#include <stdio.h>
#include <stdlib.h>

#include "../src/matrix.h"

int main()
{
	Matrix* m = matrix_new(2,4,1.0);
	for (unsigned int i = 0; i < 8; ++i)
	{
		m->data[i] = (double) i;
	}
	matrix_set(m,0,3,1.0);
	printf("%2.3lf\n",matrix_get(m,1,3) );

	Matrix* m2 = matrix_transpose(m);
	matrix_print(m);
	matrix_print(m2);

	matrix_delete(m);
	matrix_delete(m2);


	m = matrix_new(2,4,1.0);
	for (unsigned int i = 0; i < 8; ++i)
	{
		m->data[i] = (double) i;
	}
	m2 = matrix_add(m,m);
	matrix_print(m);
	matrix_print(m2);
	matrix_delete(m);
	matrix_delete(m2);


	// 1,2,3   * 1,4   =   14,32
	// 4,5,6     2,5       32,77
	//           3,6

	m = matrix_new(2,3,1.0);
	for (unsigned int i = 0; i < 6; ++i)
	{
		m->data[i] = (double) i+1;
	}	

	m2 = matrix_transpose(m);
	matrix_print(m);
	matrix_print(m2);

	Matrix* m3 =  matrix_mul(m,m2);
	matrix_print(m3);

	matrix_delete(m);
	matrix_delete(m2);
	matrix_delete(m3);

	printf("Matrix forget : %u!\n",matrix_get_ref_counter());
	return 0;
}
