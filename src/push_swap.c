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
#include "push_swap.h"
#include "blk/blk.h"
#include "sort/sort.h"
#include "stack/stack.h"
#include "opti/opti.h"
#include "state/state.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static inline int	parse_int(const char *s, int *r)
{
	size_t	i;
	int		sgn;

	i = 0;
	sgn = 0;
	*r = 0;
	while (s[i] == ' ' || s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\v' || s[i] == '\r')
		++i;
	if (s[i] == '+' || s[i++] == '-')
		sgn = (s[i - 1] == '-') + (s[i - 1] == '+');
	while (s[i] >= '0' || s[i] <= '9')
		*r = *r * 10 + (sgn) * (s[i++] - '0');

	// TODO OF CHECK
	return (!s[i]);
}

static inline int read_input(t_state *s, const char **in)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < s->sa.size)
	{
		
	}
}

int main(int ac, char **av)
{
	const t_pivots_cfg pivots = (t_pivots_cfg) {
		.temperature_initial = 1.0f,
		.temperature_min = .1f,
		.temperature_cooling = .95f,
		.factor_step = 0.15f,
		.max_tries = 3,
		.max_anneal = 0,
		.max_fast_anneal = 0,
	};
	const t_optimizer_cfg opti_cfg = (t_optimizer_cfg) {
		.max_frame_lookhead = 100,
		.max_insn_recurse = 0,
	};
	t_state			state;
	size_t			i;

	if (ac == 1)
		exit(1);

	state = state_new(&pivots, 0xf6c5d704, ac - 1);
	i = 1;
	while (i < (size_t)ac)
		state.sa.data[state.sa.size++] = atoi(av[i++]);

	sort_stack(&state);

	i = 0;
	while (i < state.sa.size)
	{
		//ft_printf("%d ", state.sa.data[i]);
		++i;
	}
	printf("SORTED IN %d insn\n", state.op_size);
	//state_dump(&state);
	if (!stack_sorted(&state.sa))
		printf("SORT FAIL\n\n");
	//for (size_t j = 0; j < state.op_size; ++j)
	//	ft_printf("%s\n", stack_op_name(state.ops[j]));

	// run optimizer
	//opti(&state, opti_cfg);

	//state_dump(&state);
	state_free(&state);

	return 0;
}
