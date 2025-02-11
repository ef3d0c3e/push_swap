#ifndef UTIL_H
# define UTIL_H

# include "state/state.h"

/**
 * @brief Memcpy implementation from libft
 */
void			*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Performs operation `op` on `sa` and `sb` and store the result in state
 *
 * @param state The @ref s_state struct
 * @param op Operation to perform
 */
void			op(t_state *state, enum e_stack_op op);

#endif // UTIL_H
