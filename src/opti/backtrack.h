#ifndef BACKTRACK_H
# define BACKTRACK_H

#include "../stack/stack.h"

typedef struct s_state		t_state;
typedef struct s_savestate	t_savestate;

/**
 * @brief Backtracking structure
 */
typedef struct s_backtrack
{
	/**
	 * @brief Number of lookahead frames
	 */
	size_t				max_frame_lookhead;
	/**
	 * @brief Maximum recursion depth (max 10)
	 *
	 * Can be increased for small sorts
	 */
	size_t				max_insn_recurse;

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

#endif // BACKTRACK_H
