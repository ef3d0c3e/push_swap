#ifndef SORT_H
# define SORT_H

# include <stdlib.h>

typedef struct s_state	t_state;
typedef struct s_blk	t_blk;

/**
 * @brief Data used by the pivot selection algorithm
 */
typedef struct s_pivots_data
{
	struct s_pivots_cfg
	{
		float	temperature_initial;
		float	temperature_min;
		float	temperature_cooling;
		float	factor_step;
		size_t	max_tries;
	} cfg;


}	t_pivots_data;
/**
 * @brief Quicksort for integer array with cmp = a < b
 */
void	quicksort(int *arr, int *indices, int low, int high);

/**
 * @brief Initializes the pivots data
 */
t_pivots_data	pivots_init(struct s_pivots_cfg cfg);

void	sort_stack(t_state *s);

/**
 * @brief Gets the next pivots
 */
void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2);


#endif // SORT_H
