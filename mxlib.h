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
	int	rows;
	int	cols;
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

# define RANDOM 1
# define ZERO 2
# define NEW 4
# define FREE 8

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


#endif
