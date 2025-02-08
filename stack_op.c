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
#include "libs/ft_printf/src/ft_printf.h"
#include "push_swap.h"
#include "stack.h"
#include <stdint.h>

/* The swap operator */
static inline void	swap_impl(const struct s_stack *s)
{
	const int	tmp = s->data[0];

	s->data[0] = s->data[1];
	s->data[1] = tmp;
}

/* The rotate operator */
static inline void	rot_impl(struct s_stack *s)
{
	const int	tmp = s->data[0];

	if (s->data == s->start + 2 * s->capacity)
	{
		ft_memcpy((int *)s->start + s->capacity, s->data, s->size);
		s->data = (int *)s->start + s->capacity;
	}

	++s->data;
	s->data[s->size-1] = tmp;
}

/* The reverse rotate operator */
static void	rrot_impl(struct s_stack *s)
{
	const int	tmp = s->data[s->size - 1];

	if (s->data == s->start)
	{
		ft_memcpy((int *)s->start + s->capacity, s->data, s->size);
		s->data = (int *)s->start + s->capacity;
	}

	--s->data;
	s->data[0] = tmp;
}

void	stack_op(struct s_stack *sa,
		struct s_stack *sb,
		enum e_stack_op op)
{
	const uint8_t			operand = op & __STACK_OPERAND;
	const uint8_t			operator = op & __STACK_OPERATOR;
	struct s_stack			*ss[2] = {sa, sb};
	size_t					i;

	i = 0;
	while (i < 2)
	{
		if (!(operand & (1 << i)) && ++i)
			continue ;
		if (operator == __STACK_OP_SWAP && ss[i]->size > 1)
			swap_impl(ss[i]);
		else if (operator == __STACK_OP_ROTATE && ss[i]->size > 1)
			rot_impl(ss[i]);
		else if (operator == __STACK_OP_REV_ROTATE && ss[i]->size > 1)
			rrot_impl(ss[i]);
		++i;
	}
	if (operator == __STACK_OP_PUSH && operand == __STACK_OP_SEL_A
		&& sb->size > 0)
		sa->data[sa->size++] = sb->data[--sb->size];
	else if (operator == __STACK_OP_PUSH && operand == __STACK_OP_SEL_B
		&& sa->size > 0)
		sb->data[sb->size++] = sa->data[--sa->size];
}
