#include <stdio.h>
#include <stdlib.h>

#include "../src/matrix.h"

int main()
{
	Matrix* m = matrix_new(3,3,0.0);
	printf("hello world!\n");
	matrix_print(m);
	matrix_delete(m);

	printf("Matrix forget : %u!\n",matrix_get_ref_counter());
	return 0;
}
