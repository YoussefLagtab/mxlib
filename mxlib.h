#ifndef MATRICES_LIBRARY
# define MATRICES_LIBRARY

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef long double ld;

typedef struct s_matrix
{
	ld	**values;
	size_t	rows;
	size_t	cols;
}				t_matrix;

/*
**	FLAGS
*/

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

# define NOTSET 1
# define RANDOM 2
# define ZERO 3
# define NEW 8
# define FREE 16
# define COMP 32
# define VERTICAL 64
# define HORIZONTAL 128

/*
**	UTILITY MACROS
*/

# define IS_SQUARE(x) (x.rows == x.cols)

/*
**	UTILITY FUNCTIONS
*/

t_matrix	*create_matrix(size_t rows, size_t cols, int flag);
void		free_matrix(t_matrix *a);
t_matrix	*copy_matrix(t_matrix *a);
t_matrix	*add_matrix(t_matrix *a, t_matrix *b, int flag);
t_matrix	*scale_matrix(t_matrix *a, long double scale, int flag);
t_matrix	*append_matrix(t_matrix *a, t_matrix *b, int flag);
t_matrix	*multiply_matrix(t_matrix *a, t_matrix *b);
t_matrix	*matrix_row(t_matrix *a, size_t r);
t_matrix	*matrix_col(t_matrix *a, size_t c);
#endif
