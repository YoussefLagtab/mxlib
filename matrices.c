#include "mxlib.h"

/*
 * return an allocated matrix with specific number of rows and columns
 * values are initialized depending on flag value:
 * 	RANDOM: assign random values
 * 	ZERO: assign zero values
*/

t_matrix	*create_matrix(size_t rows, size_t cols, int flag)
{
	t_matrix	*matrix;

	if (!rows || !cols ||
		!(matrix = malloc(sizeof(t_matrix))) ||
		!(matrix->values = (ld **)malloc(sizeof(ld *) * rows)))
		return (NULL);
	matrix->rows = rows;
	matrix->cols = cols;
	for (int i = 0; i < rows; i++)
	{
		if (!(matrix->values[i] = (ld *)malloc(sizeof(ll) * cols)))
			return (NULL);
		if (flag & ZERO)
			bzero((void *)matrix->values[i], cols * sizeof(ld));
		else if (flag & RANDOM)
			exit(0); //make some random shih
	}
	return (matrix);
}

void		free_matrix(t_matrix *a)
{
	if (!a)
		return ;
	for (int i = 0; i < a->rows; i++)
		free(a->values[i]);
	free(a->values);
	free(a);
}

t_matrix	*copy_matrix(t_matrix *a)
{
	t_matrix *copy;

	if (!a || !(copy = create_matrix(a->rows, a->cols, INT_MAX)))
		return (NULL);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			copy[i][j] += a[i][j];
}

t_matrix	*add_matrix(t_matrix *a, t_matrix *b, int flag)
{
	t_matrix *sum;

	if (!a || !b || a->rows != b->rows || a->cols != b->cols)
		return ;
	sum = flag & NEW ? copy_matrix(a) : a;
	for (int i = 0; i < sum->rows; i++)
		for (int j = 0; j < sum->cols; j++)
			sum[i][j] += b[i][j];
	if (flag & NEW && flag & FREE)
		free_matrix(a);
	return (sum);
}

t_matrix	*scale_matrix(t_matrix *a, long double scale, int flag)
{
	t_matrix *scaled;

	if (!a)
		return ;
	scaled = flag & NEW ? copy_matrix(a) : a;
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			a[i][j] *= scale;	
	if (flag & NEW && flag & FREE)
		free_matrix(a);
	return (scaled);
}

void	multiply_matrix(t_matrix *a, t_matrix *b, int flag)
{

}
