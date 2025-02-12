#ifndef OPTI_H
# define OPTI_H

#include <stdlib.h>

typedef struct s_state		t_state;

typedef struct s_optimizer_cfg
{
	/**
	 * @brief Maximum number of forward frames to search for a future value
	 *
	 * 100 should be a good value
	 */
	size_t max_frame_lookhead;
	/**
	 * @brief Maximum recursion depth (max 10)
	 */
	size_t max_insn_recurse;
}	t_optimizer_cfg;

/**
 * @brief Optimizes instructions and output final result to stdout
 *
 * @param s The state
 * @param cfg The settings for the optimizer
 */
void opti(const t_state *s, const t_optimizer_cfg cfg);

#endif // OPTI_H

