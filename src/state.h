#ifndef STATE_H
# define STATE_H

# include "blk/blk.h"
# include "stack/stack.h"

/**
 * @brief Stores state of the push_swap instance
 */
typedef struct s_state
{
	/**
	 * @brief A stack
	 */
	struct s_stack	sa;
	/**
	 * @brief B stack
	 */
	struct s_stack	sb;
	/**
	 * @brief Array of used operations
	 *
	 * This is then used for printing
	 */
	enum e_stack_op	*ops;
	/**
	 * @brief Size of the `ops` array
	 */
	size_t			op_size;
	/**
	 * @brief Capacity of the `ops` array
	 */
	size_t			op_cap;
}	t_state;

/**
 * @brief Creates a new `s_data` structure
 *
 * @param sz The size of the stacks in the s_data structure
 */
t_state			state_new(size_t sz);

/**
 * @brief Frees a `s_data` structure
 *
 * @param data Data to free
 */
void			state_free(t_state *state);

/**
 * @brief Output and clears the data's ops array
 *
 * @param data Data to display
 */
void			state_dump(t_state *state);

/**
 * @brief Generates two pivots for splitting a block
 */
void			state_pivots(t_state *state, const t_blk *blk, int *p1, int *p2);

#endif // STATE_H
