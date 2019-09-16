#include "mxlib.h"

/*            n
 *            __
 *            \
 *   c(i,j) = /__  a(i,k) * b(k,j)
 *            k = 1
*/

t_matrix	*multiply_matrix_1(t_matrix *a, t_matrix *b)
{
	t_matrix *product;

	if (!(product = create_matrix(a->rows, b->cols, NOTSET)))
		return (NULL);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < b->cols; j++)
			for (int k = 0; k < a->cols; k++)
				product[i][j] += a[i][k] * b[k][j];
	return (product);
}
