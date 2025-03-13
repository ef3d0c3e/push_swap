/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTIL_H
# define UTIL_H

# include "state/state.h"

/**
 * @brief Memcpy implementation from libft
 */
void
*ft_memcpy(void *dest, const void *src, size_t n);
/**
 * @brief Clamps value x between [min, max]
 */
float
clamp(float x, float min, float max);
/**
 * @brief `exp` function approximation
 */
float
approx_exp(float x);
/**
 * @brief Performs operation `op` on `sa` and `sb` and store the result in state
 *
 * @param state The @ref s_state struct
 * @param op Operation to perform
 */
void
op(t_state *state, enum e_stack_op op);

#endif // UTIL_H
