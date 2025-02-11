#ifndef STATE_H
# define STATE_H

# include "blk/blk.h"
# include "stack/stack.h"

/**
 * @brief Save of the state
 */
typedef struct s_savestate
{
	struct s_stack	sa;
	struct s_stack	sb;
	enum e_stack_op	*ops;
	size_t			id;
}	t_savestate;

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


	t_savestate		*saves;
	size_t			saves_size;
	size_t			saves_cap;
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
 * @brief Partially clones a sate
 *
 * This function will only clone the stack states.
 *
 * @param state The state to clone
 *
 * @returns The cloned state
 */
t_state			state_partial_clone(const t_state *state);

/**
 * @brief Constructs state from saved state
 *
 * @param save The savestate to generate a state from
 *
 * @retruns The state constructed from a savestate
 */
t_state			state_from_savestate(const t_savestate *save);

/**
 * @brief Generates two pivots for splitting a block
 */
void			state_pivots(t_state *state, const t_blk *blk, int *p1, int *p2);

#endif // STATE_H
