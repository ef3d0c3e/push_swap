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
#include "stack.h"
#include <stdint.h>

/* memmove implementation from my libft */
static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;

	if (!dest && !src)
		return (dest);
	i = 0;
	if (src < dest)
	{
		while (i < n)
		{
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
			++i;
		}
	}
	else
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			++i;
		}
	}
	return (dest);
}

/* The swap operator */
static void	swap_impl(const struct s_stack *s)
{
	int	tmp;

	tmp = s->data[s->size - 1];
	s->data[s->size - 1] = s->data[s->size - 2];
	s->data[s->size - 2] = tmp;
}

/* The rotate operator */
static void	rot_impl(const struct s_stack *s)
{
	int	tmp;

	tmp = s->data[s->size - 1];
	ft_memmove(&s->data[1], &s->data[0], (s->size - 1) * sizeof(int));
	s->data[0] = tmp;
}

/* The reverse rotate operator */
static void	rrot_impl(const struct s_stack *s)
{
	int	tmp;

	tmp = s->data[0];
	ft_memmove(&s->data[0], &s->data[1], (s->size - 1) * sizeof(int));
	s->data[s->size - 1] = tmp;
}

void	stack_op(struct s_stack *sa,
		struct s_stack *sb,
		enum e_stack_op op)
{
	const struct s_stack	*ss[2] = {sa, sb};
	const uint8_t			operand = op & __STACK_OPERAND;
	const uint8_t			operator = op & __STACK_OPERATOR;
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
