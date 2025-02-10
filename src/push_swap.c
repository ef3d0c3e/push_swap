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
#include "sort/sort.h"
#include "stack/stack.h"
#include "push_swap.h"
#include <limits.h>
#include "util.h"
#include <stddef.h>

static const int	three_permuts[6][3] = {
	{0, 1, 2},
	{0, 2, 1},
	{1, 0, 2},
	{1, 2, 0},
	{2, 0, 1},
	{2, 1, 0},
};

static const int	four_permuts[24][4] = {
	{0,1,2,3},
	{0,1,3,2},
	{0,2,1,3},
	{0,2,3,1},
	{0,3,1,2},
	{0,3,2,1},
	{1,0,2,3},
	{1,0,3,2},
	{1,2,0,3},
	{1,2,3,0},
	{1,3,0,2},
	{1,3,2,0},
	{2,0,1,3},
	{2,0,3,1},
	{2,1,0,3},
	{2,1,3,0},
	{2,3,0,1},
	{2,3,1,0},
	{3,0,1,2},
	{3,0,2,1},
	{3,1,0,2},
	{3,1,2,0},
	{3,2,0,1},
	{3,2,1,0},
};

static const int	five_permuts[120][5] = {
	{0,1,2,3,4},
	{0,1,2,4,3},
	{0,1,3,2,4},
	{0,1,3,4,2},
	{0,1,4,2,3},
	{0,1,4,3,2},
	{0,2,1,3,4},
	{0,2,1,4,3},
	{0,2,3,1,4},
	{0,2,3,4,1},
	{0,2,4,1,3},
	{0,2,4,3,1},
	{0,3,1,2,4},
	{0,3,1,4,2},
	{0,3,2,1,4},
	{0,3,2,4,1},
	{0,3,4,1,2},
	{0,3,4,2,1},
	{0,4,1,2,3},
	{0,4,1,3,2},
	{0,4,2,1,3},
	{0,4,2,3,1},
	{0,4,3,1,2},
	{0,4,3,2,1},
	{1,0,2,3,4},
	{1,0,2,4,3},
	{1,0,3,2,4},
	{1,0,3,4,2},
	{1,0,4,2,3},
	{1,0,4,3,2},
	{1,2,0,3,4},
	{1,2,0,4,3},
	{1,2,3,0,4},
	{1,2,3,4,0},
	{1,2,4,0,3},
	{1,2,4,3,0},
	{1,3,0,2,4},
	{1,3,0,4,2},
	{1,3,2,0,4},
	{1,3,2,4,0},
	{1,3,4,0,2},
	{1,3,4,2,0},
	{1,4,0,2,3},
	{1,4,0,3,2},
	{1,4,2,0,3},
	{1,4,2,3,0},
	{1,4,3,0,2},
	{1,4,3,2,0},
	{2,0,1,3,4},
	{2,0,1,4,3},
	{2,0,3,1,4},
	{2,0,3,4,1},
	{2,0,4,1,3},
	{2,0,4,3,1},
	{2,1,0,3,4},
	{2,1,0,4,3},
	{2,1,3,0,4},
	{2,1,3,4,0},
	{2,1,4,0,3},
	{2,1,4,3,0},
	{2,3,0,1,4},
	{2,3,0,4,1},
	{2,3,1,0,4},
	{2,3,1,4,0},
	{2,3,4,0,1},
	{2,3,4,1,0},
	{2,4,0,1,3},
	{2,4,0,3,1},
	{2,4,1,0,3},
	{2,4,1,3,0},
	{2,4,3,0,1},
	{2,4,3,1,0},
	{3,0,1,2,4},
	{3,0,1,4,2},
	{3,0,2,1,4},
	{3,0,2,4,1},
	{3,0,4,1,2},
	{3,0,4,2,1},
	{3,1,0,2,4},
	{3,1,0,4,2},
	{3,1,2,0,4},
	{3,1,2,4,0},
	{3,1,4,0,2},
	{3,1,4,2,0},
	{3,2,0,1,4},
	{3,2,0,4,1},
	{3,2,1,0,4},
	{3,2,1,4,0},
	{3,2,4,0,1},
	{3,2,4,1,0},
	{3,4,0,1,2},
	{3,4,0,2,1},
	{3,4,1,0,2},
	{3,4,1,2,0},
	{3,4,2,0,1},
	{3,4,2,1,0},
	{4,0,1,2,3},
	{4,0,1,3,2},
	{4,0,2,1,3},
	{4,0,2,3,1},
	{4,0,3,1,2},
	{4,0,3,2,1},
	{4,1,0,2,3},
	{4,1,0,3,2},
	{4,1,2,0,3},
	{4,1,2,3,0},
	{4,1,3,0,2},
	{4,1,3,2,0},
	{4,2,0,1,3},
	{4,2,0,3,1},
	{4,2,1,0,3},
	{4,2,1,3,0},
	{4,2,3,0,1},
	{4,2,3,1,0},
	{4,3,0,1,2},
	{4,3,0,2,1},
	{4,3,1,0,2},
	{4,3,1,2,0},
	{4,3,2,0,1},
	{4,3,2,1,0},
};

void basic_tests()
{
	struct s_state	state;
	size_t			i;
	size_t			j;

	state = state_new(3);
	i = 0;
	while (i < 6)
	{
		state.op_size = 0;
		state.sb.size = 0;
		state.sa.size = 3;
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, three_permuts[i], 3 * sizeof(int));
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
			continue;
		ft_dprintf(2, "Failed to sort permutation of 3.\nInput : ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", three_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
	}
	state_free(&state);

	i = 0;
	while (i < 24)
	{
		state = state_new(4);
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, four_permuts[i], 4 * sizeof(int));
		j = 0;
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
		{
			state_free(&state);
			continue;
		}
		ft_dprintf(2, "Failed to sort permutation of 4.\nInput : ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", four_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
		state_free(&state);
	}

	i = 0;
	while (i < 120)
	{
		state = state_new(5);
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, five_permuts[i], 5 * sizeof(int));
		j = 0;
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
		{
			state_free(&state);
			continue;
		}
		ft_dprintf(2, "Failed to sort permutation of 5.\nInput : ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", five_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
		state_free(&state);
	}
}

int main(int ac, char **av)
{
	t_state	state;
	size_t	i;

	basic_tests();
	return 0;
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
	i = 0;
	while (i < state.sa.size)
	{
		ft_printf("%d ", state.sa.data[i]);
		++i;
	}
	//state_dump(&state);
	state_free(&state);

	return 0;
}
