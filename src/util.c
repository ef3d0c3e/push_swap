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
#include <ft_printf.h>
#include "push_swap.h"
#include "state.h"
#include "stack/stack.h"

/* memcopy from my libft */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*end = (unsigned char*)src + n;
	unsigned char		*wd;
	const unsigned char	*ws;

	wd = dest;
	ws = src;
	while (end - ws >= (long int)sizeof(unsigned long int))
	{
		*(unsigned long int *)wd = *(const unsigned long int *)ws;
		wd += sizeof(unsigned long int);
		ws += sizeof(unsigned long int);
	}
	while (ws != end)
		*(wd++) = *(ws++);

	return (dest);
}


void	op(t_state *state, enum e_stack_op op)
{
	enum e_stack_op	*tmp;
	size_t			i;

	if (!state->saves)
		state_create_savestate(state);
	if (state->op_size >= state->op_cap)
	{
		tmp = malloc(sizeof(op) * ((state->op_cap + !state->op_cap) << 1));
		if (!tmp)
		{
			ft_dprintf(2, "Error\n");
			exit(1);
		}
		i = 0;
		while (i++ < state->op_size)
			tmp[i - 1] = state->ops[i - 1];
		free(state->ops);
		state->ops = tmp;
		state->op_cap = (state->op_cap + !state->op_cap) << 1;
	}
	state->ops[state->op_size++] = op;
	stack_op(&state->sa, &state->sb, op);
	state_create_savestate(state);

	// debug
	if (0)
	{
		ft_printf("%s\nA: ", stack_op_name(op));
		i = 0;
		while (i < state->sa.size)
		{
			ft_printf("%d ", state->sa.data[i]);
			++i;
		}

		ft_printf("\nB: ");
		i = 0;
		while (i < state->sb.size)
		{
			ft_printf("%d ", state->sb.data[i]);
			++i;
		}
		ft_printf("\n-----\n");
	}
}
