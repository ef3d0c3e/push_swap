/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "opti/opti.h"
#include "state/state.h"
#include "args.h"

#include <ft_printf.h>

int	main(int ac, char **av)
{
	const t_pivots_cfg		pivots = (t_pivots_cfg){
		.temperature_initial = 1.0f,
		.temperature_min = .1f,
		.temperature_cooling = .99f,
		.factor_step = 0.5f,
		.max_tries = 100,
		.max_anneal = 1,
	};
	const t_optimizer_cfg	opti_cfg = (t_optimizer_cfg){
		.max_frame_lookhead = 100,
		.max_insn_recurse = 2,
	};
	t_state					state;

	state = parse_args(&pivots, ac, av);
	sort_stack(&state);
	opti(&state, opti_cfg);
	state_free(&state);
	return (0);
}
