#include "mxlib.h"

/*
 * return an allocated matrix with specific number of rows and columns
 * values are initialized depending on flag value:
 * 	RANDOM: assign random values
 * 	ZERO: assign zero values
 */

t_matrix *create_matrix(size_t rows, size_t cols, int flag)
{
	t_matrix *matrix;

	if (!rows || !cols ||
		!(matrix = malloc(sizeof(t_matrix))) ||
		!(matrix->values = (ld **)malloc(sizeof(ld *) * rows)))
		return (NULL);
	matrix->rows = rows;
	matrix->cols = cols;
	for (int i = 0; i < rows; i++)
	{
		if (!(matrix->values[i] = (ld *)malloc(sizeof(ld) * cols)))
			return (NULL);
		if (flag & ZERO)
			bzero((void *)matrix->values[i], cols * sizeof(ld));
		else if (flag & RANDOM)
			exit(0); //make some random shih
	}
	return (matrix);
}

void free_matrix(t_matrix *a)
{
	if (!a)
		return;
	for (int i = 0; i < a->rows; i++)
		free(a->values[i]);
	free(a->values);
	free(a);
}

t_matrix *copy_matrix(t_matrix *a)
{
	t_matrix *copy;

	if (!a || !(copy = create_matrix(a->rows, a->cols, NOTSET)))
		return (NULL);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			(copy->values)[i][j] += (a->values)[i][j];
}

t_matrix *add_matrix(t_matrix *a, t_matrix *b, int flag)
{
	t_matrix *sum;

	if (!a || !b || a->rows != b->rows || a->cols != b->cols)
		return (NULL);
	if (!(sum = flag & NEW ? copy_matrix(a) : a))
		return (NULL);
	for (int i = 0; i < sum->rows; i++)
		for (int j = 0; j < sum->cols; j++)
			(sum->values)[i][j] += (b->values)[i][j];
	if (flag & NEW && flag & FREE)
		free_matrix(a);
	return (sum);
}

t_matrix *scale_matrix(t_matrix *a, long double scale, int flag)
{
	t_matrix *scaled;

	if (!a || !(scaled = flag & NEW ? copy_matrix(a) : a))
		return (NULL);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			(a->values)[i][j] *= scale;
	if (flag & NEW && flag & FREE)
		free_matrix(a);
	return (scaled);
}

t_matrix *multiply_matrix(t_matrix *a, t_matrix *b)
{
	t_matrix *product;

	if (!a || !b || a->rows != b->cols ||
		!(product = create_matrix(a->rows, b->cols, NOTSET)))
		return (NULL);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < b->cols; j++)
			for (int k = 0; k < a->cols; k++)
				(product->values)[i][j] += (a->values)[i][k] * (b->values)[k][j];
	return (product);
}

t_matrix *append_matrix(t_matrix *a, t_matrix *b, int flag)
{
	t_matrix *appended;

	if (!a || !b || (!(flag & VERTICAL) && !(flag & HORIZONTAL)) ||
				flag & VERTICAL
			? a->rows != b->rows
			: a->cols != b->cols ||
				  !(appended = create_matrix(
						flag & VERTICAL ? a->rows + b->rows : a->rows,
						flag & HORIZONTAL ? a->cols + b->cols : a->cols,
						NOTSET)))
		return (NULL);
	for (int i = 0; i < appended->rows; i++)
	{
		for (int j = 0; j < appended->cols; j++)
		{
			(appended->values)[i][j] = i > a->rows ? (b->values)[i - a->rows][j] : j > a->cols ? (b->values)[i][j - a->cols] : (a->values)[i][j];
		}
	}
	return (appended);
}

t_matrix *matrix_partition(t_matrix *a, size_t rl, size_t rr, size_t cl, size_t cr)
{
	t_matrix *partition;

	if (!a || rl > a->rows || rr > a->rows || cl > a->cols || cr > a->cols || rl > rr || cl > cr ||
		!(partition = create_matrix(rr - rl + 1, cr - cl + 1, NOTSET)))
		return (NULL);
	for (int i = rl; i <= rr; i++)
		for (int j = cl; j <= cr; j++)
			partition->values[i = rl][j - cl] = a->values[i][j];
	return (partition);
}

t_matrix *matrix_row(t_matrix *a, size_t r)
{
	return (matrix_partition(a, r, r, 0, a ? a->cols : 69));
}

t_matrix *matrix_col(t_matrix *a, size_t c)
{
	return (matrix_partition(a, 0, a ? a->rows : 69, c, c));
}

t_matrix *matrix_tanspose(t_matrix *a)
{
	t_matrix *transpose;

	if (!a || (transpose = create_matrix(a->cols, a->rows, NOTSET)))
		return (NULL);
	for (int i = 0; i < a->cols; i++)
		for (int j = 0; j < a->rows; j++)
			transpose->values[i][j] = a->values[j][i];
	return (transpose);
}
