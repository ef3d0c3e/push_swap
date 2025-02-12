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

#include <ft_printf.h>
#include <limits.h>
#include <stddef.h>


void basic_tests();

static void ps(const char *name, const t_state *s)
{
	ft_printf(" [ STATE: %s ]\n", name);
	ft_printf("OP | ");

	for (size_t i = 0; i < s->op_size; ++i)
		ft_printf(" %s", stack_op_name(s->ops[i]));

	ft_printf("\n A | ");
	for (size_t i = 0; i < s->sa.size; ++i)
		ft_printf(" %d", s->sa.data[i]);
	ft_printf("\n B | ");
	for (size_t i = 0; i < s->sb.size; ++i)
		ft_printf(" %d", s->sb.data[i]);
	ft_printf("\n");
}

int main(int ac, char **av)
{
	const t_pivots_cfg pivots = (t_pivots_cfg) {
		.temperature_initial = 2.0f,
		.temperature_min = .1f,
		.temperature_cooling = .85f,
		.factor_step = 0.1f,
		.max_tries = 4,
		.max_anneal = 2,
	};
	const t_optimizer_cfg opti_cfg = (t_optimizer_cfg) {
		.max_frame_lookhead = 100,
		.max_insn_recurse = 2,
	};
	t_state			state;
	size_t			i;

	//basic_tests();
	//return 0;
	if (ac == 1)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}

	state = state_new(&pivots, 0xB00B1E5, ac - 1);
	i = 1;
	while (i < (size_t)ac)
		state.sa.data[state.sa.size++] = atoi(av[i++]);

	sort_stack(&state);

	ps("After Sort", &state);
	i = 0;
	while (i < state.sa.size)
	{
		//ft_printf("%d ", state.sa.data[i]);
		++i;
	}
	ft_printf("SORTED IN %d insn\n", state.op_size);
	//state_dump(&state);
	if (!stack_sorted(&state.sa))
		ft_printf("SORT FAIL\n\n");
	//for (size_t j = 0; j < state.op_size; ++j)
	//	ft_printf("%s\n", stack_op_name(state.ops[j]));

	// run optimizer
	opti(&state, opti_cfg);

	state_free(&state);

	return 0;
}
