/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.h:                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef OPTI_H
# define OPTI_H

# include <stdlib.h>

typedef struct s_state		t_state;

/**
 * @brief Config for the instruction optimizer
 */
typedef struct s_optimizer_cfg
{
	/**
	 * @brief Maximum number of forward frames to search for a future value
	 *
	 * 100 should be a good value
	 */
	size_t	max_frame_lookhead;
	/**
	 * @brief Maximum recursion depth (max 10)
	 */
	size_t	max_insn_recurse;
}	t_optimizer_cfg;

/**
 * @brief Optimizes instructions and output final result to stdout
 *
 * @param s The state
 * @param cfg The settings for the optimizer
 *
 * @returns The new state simulated from optimized instructions
 */
void
opti(const t_state *s, const t_optimizer_cfg cfg);

#endif // OPTI_H
