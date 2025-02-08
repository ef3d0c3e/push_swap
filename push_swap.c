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
#include "libs/ft_printf/src/ft_printf.h"
#include "libs/ft_printf/src/ft_printf_bonus.h"
#include "stack.h"
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

void basic_tests()
{
	struct s_data	data;
	size_t			i;
	size_t			j;

	data = data_new(3);
	data.sa.size = 3;
	i = 0;
	while (i < 6)
	{
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
}

int main(int ac, char **av)
{
	struct s_data	data;
	size_t			i;

	basic_tests();
	return 0;
	if (ac < 2)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}
	data = data_new(ac - 1);
	i = 1;
	while (i < (size_t)ac)
		data.sa.data[data.sa.size++] = atoi(av[i++]);

	sort_stack(&data);
	i = 0;
	ft_printf("---\n");
	while (i < data.sa.size)
	{
		ft_printf("%d ", data.sa.data[i]);
		++i;
	}
	data_dump(&data);
	data_free(&data);

	return 0;
}
