/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ft_printf.h>
#include "stack.h"
#include "../util.h"

/* The swap operator */
static inline void	swap_impl(
		const struct s_stack *s)
{
	const int	tmp = s->data[0];

	s->data[0] = s->data[1];
	s->data[1] = tmp;
}

/* The rotate operator */
static inline void	rot_impl(
		struct s_stack *s)
{
	const int	tmp = s->data[0];

	if (s->data + 1 >= s->start + 2 * s->capacity)
	{
		ft_memcpy((int *)s->start + s->capacity, s->data,
			s->size * sizeof(int));
		s->data = (int *)s->start + s->capacity;
	}
	++s->data;
	s->data[s->size - 1] = tmp;
}

/* The reverse rotate operator */
static inline void	rrot_impl(
		struct s_stack *s)
{
	const int	tmp = s->data[s->size - 1];

	if (s->data - 1 <= s->start)
	{
		ft_memcpy((int *)s->start + s->capacity,
			s->data, s->size * sizeof(int));
		s->data = (int *)s->start + s->capacity;
	}
	--s->data;
	s->data[0] = tmp;
}

/* Push implementation */
static inline void	push_impl(
		struct s_stack *from,
		struct s_stack *to)
{
	if (to->data - 1 <= to->start)
	{
		ft_memcpy((int *)to->start + to->capacity,
			to->data, to->size * sizeof(int));
		to->data = (int *)to->start + to->capacity;
	}
	--to->data;
	++to->size;
	to->data[0] = from->data[0];
	++from->data;
	--from->size;
}

void	stack_op(
		struct s_stack *sa,
		struct s_stack *sb,
		enum e_stack_op op)
{
	struct s_stack *const	ss[2] = {sa, sb};
	const enum e_stack_op	operand = op & __STACK_OPERAND;
	const enum e_stack_op	operator = op & __STACK_OPERATOR;
	size_t					i;

	i = 0;
	while (i < 2)
	{
		if (!(operand & (1 << i)) && ++i)
			continue ;
		else if (operator == __STACK_OP_SWAP && ss[i]->size >= 2)
			swap_impl(ss[i]);
		else if (operator == __STACK_OP_ROTATE && ss[i]->size >= 2)
			rot_impl(ss[i]);
		else if (operator == __STACK_OP_REV_ROTATE && ss[i]->size >= 2)
			rrot_impl(ss[i]);
		else if (operator == __STACK_OP_PUSH && ss[!i]->size >= 1)
			push_impl(ss[!i], ss[i]);
		++i;
	}
}
