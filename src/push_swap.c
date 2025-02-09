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
#include "stack/stack.h"
#include "push_swap.h"
#include <limits.h>
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
	struct s_data	data;
	size_t			i;
	size_t			j;

	data = data_new(3);
	i = 0;
	while (i < 6)
	{
		data.op_size = 0;
		data.sb.size = 0;
		data.sa.size = 3;
		data.sa.data = (int*)data.sa.start + data.sa.capacity;
		ft_memcpy(data.sa.data, three_permuts[i], 3 * sizeof(int));
		sort_stack(&data);
		++i;
		if (sorted(&data.sa))
			continue;
		ft_dprintf(2, "Failed to sort permutation of 3.\nInput : ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", three_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", data.sa.data[j++]);
		ft_dprintf(2, "\n");
	}
	data_free(&data);

	data = data_new(4);
	i = 0;
	while (i < 24)
	{
		data.op_size = 0;
		data.sb.size = 0;
		data.sa.size = 4;
		data.sa.data = (int*)data.sa.start + data.sa.capacity;
		ft_memcpy(data.sa.data, four_permuts[i], 4 * sizeof(int));
		sort_stack(&data);
		++i;
		if (sorted(&data.sa))
			continue;
		ft_dprintf(2, "Failed to sort permutation of 4.\nInput : ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", four_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", data.sa.data[j++]);
		ft_dprintf(2, "\n");
	}
	data_free(&data);

	data = data_new(5);
	i = 0;
	while (i < 120)
	{
		data.op_size = 0;
		data.sb.size = 0;
		data.sa.size = 5;
		data.sa.data = (int*)data.sa.start + data.sa.capacity;
		ft_memcpy(data.sa.data, five_permuts[i], 5 * sizeof(int));
		sort_stack(&data);
		++i;
		if (sorted(&data.sa))
			continue;
		ft_dprintf(2, "Failed to sort permutation of 5.\nInput : ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", five_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", data.sa.data[j++]);
		ft_dprintf(2, "\n");
	}
	data_free(&data);
}

int main(int ac, char **av)
{
	struct s_data	data;
	size_t			i;

	//basic_tests();
	//return 0;
	if (ac == 1)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}
	data = data_new(ac - 1);
	i = 1;
	while (i < (size_t)ac)
		data.sa.data[data.sa.size++] = atoi(av[i++]);

	//op(&data, STACK_OP_PB);
	//op(&data, STACK_OP_PB);
	//op(&data, STACK_OP_PB);
	sort_stack(&data);
	i = 0;
	while (i < data.sa.size)
	{
		ft_printf("%d ", data.sa.data[i]);
		++i;
	}
	//data_dump(&data);
	data_free(&data);

	return 0;
}
