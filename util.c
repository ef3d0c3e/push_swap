/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libs/ft_printf/src/ft_printf.h"
#include "libs/ft_printf/src/ft_printf_bonus.h"
#include "push_swap.h"

void	op(struct s_data *data, enum e_stack_op op)
{
	enum e_stack_op	*tmp;
	size_t			i;

	if (data->op_size >= data->op_cap)
	{
		tmp = malloc(sizeof(op) * ((data->op_cap + !data->op_cap) << 1));
		if (!tmp)
		{
			ft_dprintf(2, "Error\n");
			exit(1);
		}
		i = 0;
		while (i++ < data->op_size)
			tmp[i - 1] = data->ops[i - 1];
		free(data->ops);
		data->ops = tmp;
		data->op_cap = (data->op_cap + !data->op_cap) << 1;
	}
	data->ops[data->op_size++] = op;
	// TODO: Print at the end, after optimizing
	ft_printf("%s\n", stack_op_name(op));
	stack_op(&data->sa, &data->sb, op);
}

int	sorted(const struct s_stack *s)
{
	size_t	i;

	if (s->size < 2)
		return (1);
	i = 1;
	while (i < s->size)
	{
		if (s->data[i - 1] > s->data[i])
			return (0);
		++i;
	}
	return (1);
}
