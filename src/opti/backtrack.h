#ifndef BACKTRACK_H
# define BACKTRACK_H

#include "../stack/stack.h"
#include "opti.h"

typedef struct s_state		t_state;
typedef struct s_savestate	t_savestate;

/**
 * @brief Backtracking structure
 */
typedef struct s_backtrack
{
	/**
	 * @brief Reference to the original state's saves
	 */
	const t_savestate	*saves;
	/**
	 * @brief Number of saves
	 */
	size_t				saves_size;
	/**
	 * @brief Index in the saves
	 */
	size_t				index;

	/**
	 * @brief Best found instruction len so far
	 */
	size_t				best_len;
	/**
	 * @brief Best skip found so far
	 */
	size_t				best_skip;
	/**
	 * @brief Operations that led to the `best_skip`
	 */
	enum e_stack_op		best_ops[10];
	/**
	 * @brief Current operations
	 */
	enum e_stack_op		ops[10];
	/**
	 * @brief Optimizer settings
	 */
	t_optimizer_cfg		cfg;
}	t_backtrack;

/**
 * @brief Compares a state with a savestate
 *
 * @param s State
 * @param ss Savestate
 *
 * @returns 1 If both states have the same stacks
 */
int	bt_compare_states(const t_state *s, const t_savestate *ss);


/**
 * @brief Find a corresponding future state to the current state, returns the number of skipped frames
 *
 * @param bt The backtracking
 * @param start Future start index
 * @param state The state
 */
size_t bt_find_future(const t_backtrack *bt, const size_t start, const t_state* state);

#endif // BACKTRACK_H
