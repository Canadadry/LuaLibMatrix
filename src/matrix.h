#ifndef __MATRIX__
#define __MATRIX__


typedef struct{
	double* data;
	unsigned int rows;
	unsigned int columns;
} Matrix;

Matrix*       matrix_new(unsigned int rows,unsigned int columns, double defaultValue);
void          matrix_init_with_pre_malloc(unsigned int rows,unsigned int columns, double defaultValue, void* dst);
void          matrix_delete(Matrix* matrix);
unsigned char matrix_is_valid(Matrix* matrix);
unsigned char matrix_copy(Matrix* in, Matrix* out);
unsigned char matrix_transpose(Matrix* in,Matrix* out);
double        matrix_get(Matrix* matrix, unsigned int row, unsigned int column);
void          matrix_set(Matrix* matrix, unsigned int row, unsigned int column,double value);
void          matrix_print(Matrix* matrix,char* string, unsigned int strSize);
unsigned char matrix_add(Matrix* m1, Matrix* m2);
void          matrix_addnum(Matrix* matrix,double value);
unsigned char matrix_sub(Matrix* m1, Matrix* m2);
unsigned char  matrix_mul(Matrix* m1, Matrix* m2,Matrix* out);
void          matrix_mulnum(Matrix* matrix, double value);
unsigned char matrix_hadamard_mul(Matrix* m1, Matrix* m2);
unsigned char matrix_is_equal(Matrix* m1, Matrix* m2);

size_t        matrix_data_size(Matrix* m);



unsigned int  matrix_get_ref_counter();

#endif
