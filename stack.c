/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stack.h"
#include "libs/ft_printf/src/ft_printf_bonus.h"

struct s_stack	stack_new(size_t capacity)
{
	int	*data;

	data = malloc(capacity * sizeof(int));
	if (!data)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}
	return ((struct s_stack){
		.data = data,
		.size = 0,
		.capacity = capacity,
	});
}

void	stack_free(struct s_stack *s)
{
	free(s->data);
}

const char	*stack_op_name(enum e_stack_op op)
{
	const static char	*names[] = {
	[STACK_OP_SA] = "sa",
	[STACK_OP_SB] = "sb",
	[STACK_OP_SS] = "ss",
	[STACK_OP_PA] = "pa",
	[STACK_OP_PB] = "pb",
	[STACK_OP_RA] = "ra",
	[STACK_OP_RB] = "rb",
	[STACK_OP_RR] = "rr",
	[STACK_OP_RRA] = "rra",
	[STACK_OP_RRB] = "rrb",
	[STACK_OP_RRR] = "rrr"
	};

	return (names[op]);
}
