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

Matrix* matrix_copy(Matrix* matrix)
{
	Matrix* out = matrix_new(matrix->rows,matrix->columns,0.0);
	const unsigned int size = matrix->rows*matrix->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		out->data[i] = matrix->data[i];
	}
	return out;
}

Matrix* matrix_transpose(Matrix* matrix)
{
	Matrix* out = matrix_new(matrix->columns,matrix->rows,0.0);
	for (unsigned int i = 0; i < matrix->rows; i++)
	{	
		for (unsigned int j = 0; j < matrix->columns; j++)
		{
			out->data[i+j*matrix->rows] = matrix->data[j+i*matrix->columns];
		}
	}
	return out;
}


double matrix_get(Matrix* matrix, unsigned int row, unsigned int column)
{
	return matrix->data[column+row*matrix->columns];
}

void   matrix_set(Matrix* matrix, unsigned int row, unsigned int column,double value)
{
	matrix->data[column+row*matrix->columns] = value;
}

void matrix_print(Matrix* matrix)
{
	if (matrix_is_valid(matrix) == 0) return;

	printf("row %u, columns %u \n",matrix->rows,matrix->columns);
	for (unsigned int i = 0; i < matrix->rows; i++)
	{	
		for (unsigned int j = 0; j < matrix->columns; j++)
		{
			printf("%2.3lf,",matrix->data[j+i*matrix->columns]);
		}
		printf("\n");
	}
	printf("\n");

}

Matrix* matrix_add(Matrix* m1, Matrix* m2)
{
	if(m1->columns != m2->columns || m1->rows != m2->rows) return 0;

	Matrix* out = matrix_new(m1->rows,m1->columns,0.0);
	const unsigned int size = m1->rows*m1->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		out->data[i] = m1->data[i] + m2->data[i];
	}
	return out;
}


unsigned int matrix_get_ref_counter()
{
	return ref_counting;
}
