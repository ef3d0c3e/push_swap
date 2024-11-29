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
#include "push_swap.h"
#include <limits.h>
#include <stddef.h>



int main(int ac, char **av)
{
	struct s_data	data;
	size_t			i;

	if (ac < 2)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}
	data = data_new(ac - 1);
	i = 1;
	while (i < ac)
		data.sa.data[data.sa.size++] = atoi(av[i++]);

	sort_stack(&data);
	i = 0;
	ft_printf("---\n");
	while (i < data.sa.size)
	{
		ft_printf("%d ", data.sa.data[i]);
		++i;
	}
	data_free(&data);

	return 0;
}
