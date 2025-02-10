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
#include <ft_printf.h>
#include "blk/blk.h"
#include "sort/sort.h"
#include "stack/stack.h"
#include "push_swap.h"
#include <limits.h>
#include <stddef.h>

#include "opti/opti.h"

void basic_tests();

int main(int ac, char **av)
{
	t_state	state;
	size_t	i;

	//basic_tests();
	//return 0;
	if (ac == 1)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}
	state = state_new(ac - 1);
	i = 1;
	while (i < (size_t)ac)
		state.sa.data[state.sa.size++] = atoi(av[i++]);

	//op(&state, STACK_OP_PB);
	//op(&state, STACK_OP_PB);
	//op(&state, STACK_OP_PB);
	sort_stack(&state);
	//blk_move(&state, BLK_A_TOP, BLK_B_TOP);
	//blk_move(&state, BLK_A_TOP, BLK_B_TOP);
	//blk_move(&state, BLK_A_TOP, BLK_B_TOP);
	//blk_move(&state, BLK_B_BOT, BLK_A_BOT);
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

	// run optimizer
	opti(&state);

	state_free(&state);

	return 0;
}
