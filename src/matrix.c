#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

unsigned int ref_counting = 0;

Matrix* matrix_new(unsigned int rows,unsigned int columns, double defaultValue)
{
	if(rows < 1 || columns < 1) return 0;

	Matrix* m = malloc(sizeof(Matrix));
	m->rows = rows;
	m->columns = columns;
	m->data = malloc(matrix_data_size(m));

	const unsigned int size = rows*columns;
	for (unsigned int i = 0; i < size; i++)
	{
		m->data[i] = defaultValue;
	}
	ref_counting++;
	return m;
}

void matrix_init_with_pre_malloc(unsigned int rows,unsigned int columns, double defaultValue, void* dst)
{
	if(rows < 1 || columns < 1) return ;

	Matrix* m = (Matrix* ) dst;
	m->rows = rows;
	m->columns = columns;
	m->data = (double*)( dst + sizeof(Matrix));

	const unsigned int size = rows*columns;
	for (unsigned int i = 0; i < size; i++)
	{
		m->data[i] = defaultValue;
	}
	return ;
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

unsigned char  matrix_is_valid(Matrix* matrix)
{
	if(matrix == 0) return 0;
	if(matrix->data == 0) return 0;
	if(matrix->columns < 1) return 0;
	if(matrix->rows < 1) return 0;

	return 1;
}

unsigned char matrix_copy(Matrix* in, Matrix* out)
{
	if(matrix_data_size(out) != matrix_data_size(in)) return 0;
	out->rows = in->rows;
	out->columns = in->columns;
	memcpy(out->data, in->data,matrix_data_size(out));
	return 1;
}

unsigned char matrix_transpose(Matrix* in,Matrix* out)
{

	if(in->columns != out->rows || in->rows != out->columns) return 0;
	for (unsigned int i = 0; i < in->rows; i++)
	{	
		for (unsigned int j = 0; j < in->columns; j++)
		{
			out->data[i+j*in->rows] = in->data[j+i*in->columns];
		}
	}
	return 1;
}


double matrix_get(Matrix* matrix, unsigned int row, unsigned int column)
{
	return matrix->data[column+row*matrix->columns];
}

void   matrix_set(Matrix* matrix, unsigned int row, unsigned int column,double value)
{
	matrix->data[column+row*matrix->columns] = value;
}

void    matrix_print(Matrix* matrix, char* str, unsigned int strSize)
{	
	if (matrix_is_valid(matrix) == 0) return;

	const unsigned int maxSizeCell = 20;
	const unsigned int headerSize = 50;
	const unsigned int sizeRequiredToPrint = matrix->rows*matrix->columns*maxSizeCell+headerSize;

	if (strSize < sizeRequiredToPrint) return;

	char cell[maxSizeCell];

	sprintf(str,"row %u, columns %u \n",1,2);//matrix->rows,matrix->columns);
	for (unsigned int i = 0; i < matrix->rows; i++)
	{	
		for (unsigned int j = 0; j < matrix->columns; j++)
		{
			sprintf(cell,"%2.3lf,",matrix->data[j+i*matrix->columns]);
			strcat(str,cell);
		}
		strcat(str,"\n");
	}
	strcat(str,"\n");

}

unsigned char matrix_add(Matrix* m1, Matrix* m2)
{
	if(m1->columns != m2->columns || m1->rows != m2->rows) return 0;

	Matrix* out = m1;
	const unsigned int size = m1->rows*m1->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		out->data[i] = m1->data[i] + m2->data[i];
	}
	return 1;
}

void matrix_addnum(Matrix* matrix,double value)
{
	const unsigned int size = matrix->rows*matrix->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		matrix->data[i] = matrix->data[i] + value;
	}
}

unsigned char matrix_sub(Matrix* m1, Matrix* m2)
{
	if(m1->columns != m2->columns || m1->rows != m2->rows) return 0;

	const unsigned int size = m1->rows*m1->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		m1->data[i] = m1->data[i] - m2->data[i];
	}
	return 1;
}

unsigned char  matrix_mul(Matrix* m1, Matrix* m2,Matrix* out)
{
	if( m1->columns != m2->rows     ) return 0;
	if( m1->rows    != out->rows    ) return 0;
	if( m2->columns != out->columns ) return 0;

	for (unsigned int i = 0; i < m1->rows; i++)
	{	
		for (unsigned int j = 0; j < m2->columns; j++)
		{
			double result = 0.0;
			for (unsigned int k = 0; k < m2->rows; k++)
			{
				result += m1->data[k+i*m1->columns] * m2->data[j+k*m2->columns];
			}
			out->data[i+j*out->columns] = result;	
		}
	}
	return 1;
}


void matrix_mulnum(Matrix* matrix, double value)
{
	const unsigned int size = matrix->rows*matrix->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		matrix->data[i] = matrix->data[i] * value;
	}
}

unsigned char matrix_hadamard_mul(Matrix* m1, Matrix* m2)
{
	if(m1->columns != m2->columns || m1->rows != m2->rows) return 0;

	const unsigned int size = m1->rows*m1->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		m1->data[i] = m1->data[i] * m2->data[i];
	}
	return 1;
}

unsigned char matrix_is_equal(Matrix* m1, Matrix* m2)
{
	if (m1 == m2 ) return 1;
	if(m1->columns != m2->columns || m1->rows != m2->rows) return 0;
	if( m1->data == m2->data ) return 1;
	const double epsilon = 0.000000000001;

	const unsigned int size = m1->rows*m1->columns;
	for (unsigned int i = 0; i < size; i++)
	{
		if( fabs(m1->data[i] - m2->data[i]) > epsilon ) return 0;
	}
	return 1;
}


size_t matrix_data_size(Matrix* m)
{
	return sizeof(double)*m->rows*m->columns;
}

unsigned int matrix_get_ref_counter()
{
	return ref_counting;
}

