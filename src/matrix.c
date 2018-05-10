#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

unsigned int ref_counting = 0;

Matrix* matrix_new(unsigned int rows,unsigned int columns, double defaultValue)
{
	if(rows < 1 || columns < 1) return 0;

	Matrix* m = malloc(sizeof(Matrix));
	m->rows = rows;
	m->columns = columns;
	m->data = malloc(sizeof(double)*rows*columns);

	const unsigned int size = rows*columns;
	for (unsigned int i = 0; i < size; i++)
	{
		m->data[i] = defaultValue;
	}
	ref_counting++;
	return m;
}

void  matrix_delete(Matrix* matrix)
{
	if (matrix == 0) return;
	if (matrix->data != 0)
	{
		free(matrix->data);
	}
	free(matrix);
	ref_counting--;
}

unsigned int  matrix_is_valid(Matrix* matrix)
{
	if(matrix == 0) return 0;
	if(matrix->data == 0) return 0;
	if(matrix->columns < 1) return 0;
	if(matrix->columns < 1) return 0;

	return 1;
}

void matrix_print(Matrix* matrix)
{
	if (matrix_is_valid(matrix) == 0) return;

	printf("row %u, columns %u \n",matrix->rows,matrix->columns);
	for (unsigned int i = 0; i < matrix->rows; i++)
	{	
		for (unsigned int j = 0; j < matrix->columns; j++)
		{
			printf("%2.3lf,",matrix->data[i+j*matrix->columns]);
		}
		printf("\n");
	}
	printf("\n");


}



unsigned int matrix_get_ref_counter()
{
	return ref_counting;
}
