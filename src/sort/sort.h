#ifndef SORT_H
# define SORT_H

# include <stdlib.h>

typedef struct s_state	t_state;
typedef struct s_blk	t_blk;

/**
 * @brief Data used by the pivot selection algorithm
 */
typedef struct s_pivots_cfg
{
	/**
	 * @brief Initial temperature
	 *
	 * A value between 0.5 and 5.0 should do it
	 */
	float	temperature_initial;
	/**
	 * @brief Minimum temperature before stopping
	 */
	float	temperature_min;
	/**
	 * @brief Temperature cooling rate [0, 1]
	 */
	float	temperature_cooling;
	/**
	 * @brief A factor of how much to step
	 */
	float	factor_step;
	/**
	 * @brief Maximum number of tries
	 */
	size_t	max_tries;
	/**
	 * @brief Max anealing depth
	 *
	 * @warn This has a huge impact on performances.
	 *
	 * When max annealing has been reached, a faster algorithm will be used
	 */
	size_t	max_anneal;
	/**
	 * @brief Max fast anealing depth
	 *
	 * @warn This has a huge impact on performances.
	 *
	 * When max fast annealing has been reached, defaults pivots (quartiles)
	 * will be used as a fallback.
	 */
	size_t	max_fast_anneal;
}	t_pivots_cfg;

/**
 * @brief Quicksort for integer array with cmp = a < b
 *
 * @param arr Array to sort
 * @param low Lower bound (initially 0)
 * @param high High bound (initially size - 1)
 */
void	quicksort(int *arr, int low, int high);
/**
 * @brief Modified quicksort that also sorts indices following the order in arr
 *
 * @param arr Array to sort
 * @param indices Indices array that will be swapped in the same way as `arr`
 * @param low Lower bound (initially 0)
 * @param high High bound (initially size - 1)
 */
void	quicksort_indices(int *arr, int *indices, int low, int high);

void	sort_stack(t_state *s);

/**
 * @brief Performs simulated annealing to select the best pivots
 *
 * Settings are controlled by the `t_pivots_cfg` structure
 *
 * @param s State to find pivots for
 * @param blk Block to find pivots for
 * @param f1 (output) First pivot
 * @param f2 (output) Second pivot
 */
void	annealing_precise(t_state *s, const t_blk *blk, float *f1, float *f2);

void	annealing_fast(t_state *s, const t_blk *blk, float *f1, float *f2);

/**
 * @brief Gets the next pivots
 *
 * @param s State to find pivots for
 * @param blk Block to find pivots for
 * @param p1 (output) First pivot value
 * @param p2 (output) Second pivot value
 */
void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2);


#endif // SORT_H
