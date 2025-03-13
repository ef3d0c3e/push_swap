/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include <stdint.h>
#include <stdlib.h>
#include <ft_printf.h>

t_state
	state_new(const t_pivots_cfg *pivots, uint32_t seed, size_t sz)
{
	int	*buf;

	buf = malloc(sz * sizeof(int));
	if (!buf)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}
	return ((t_state){
		.sa = stack_new(sz),
		.sb = stack_new(sz),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
		.tmp_buffer = buf,
		.seed = seed,
		.annealing_depth = 0,
		.pivots = pivots,
	});
}

void
	state_free(t_state *state)
{
	while (state->saves_size--)
	{
		stack_free(&state->saves[state->saves_size].sa);
		stack_free(&state->saves[state->saves_size].sb);
	}
	stack_free(&state->sa);
	stack_free(&state->sb);
	free(state->ops);
	free(state->saves);
	free(state->tmp_buffer);
}

void
	state_dump(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < state->op_size)
		ft_printf("%s\n", stack_op_name(state->ops[i++]));
	state->op_size = 0;
}

uint32_t
	state_random(t_state *s)
{
	uint32_t	x;
	uint32_t	tmp;

	x = s->seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	tmp = s->seed;
	s->seed = x;
	return (tmp);
}
