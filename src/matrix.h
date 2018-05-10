#ifndef __MATRIX__
#define __MATRIX__


typedef struct{
	double* data;
	unsigned int rows;
	unsigned int columns;
} Matrix;

Matrix*       matrix_new(unsigned int rows,unsigned int columns, double defaultValue);
void          matrix_delete(Matrix* matrix);
unsigned int  matrix_is_valid(Matrix* matrix);
Matrix*       matrix_copy(Matrix* matrix);
Matrix*       matrix_transpose(Matrix* matrix);
double        matrix_get(Matrix* matrix, unsigned int row, unsigned int column);
void          matrix_set(Matrix* matrix, unsigned int row, unsigned int column,double value);
void          matrix_print(Matrix* matrix);
Matrix*       matrix_add(Matrix* m1, Matrix* m2);
Matrix*       matrix_addnum(Matrix* matrix,double value);
Matrix*       matrix_sub(Matrix* m1, Matrix* m2);
Matrix*       matrix_mul(Matrix* m1, Matrix* m2);
Matrix*       matrix_mulnum(Matrix* m1, Matrix* m2);
Matrix*       matrix_hadamard_mul(Matrix* matrix,double value);
unsigned char matrix_is_equal(Matrix* m1, Matrix* m2);

unsigned int  matrix_get_ref_counter();

#endif
