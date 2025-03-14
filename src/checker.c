/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "args.h"
#include "ft_printf.h"
#include "stack/stack.h"
#include "state/state.h"
#include "util.h"

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static int	ft_token(const char *s, const char *token)
{
	while (*s == *token && *token)
	{
		++s;
		++token;
	}
	return (*s == '\n' && !*token);
}

static enum e_stack_op	parse_op(const char *s, size_t *pos)
{
	const enum e_stack_op	op = STACK_OP_PA * ft_token(s + *pos, "pa")
		+ STACK_OP_PB * ft_token(s + *pos, "pb")
		+ STACK_OP_SA * ft_token(s + *pos, "sa")
		+ STACK_OP_SB * ft_token(s + *pos, "sb")
		+ STACK_OP_SS * ft_token(s + *pos, "ss")
		+ STACK_OP_RA * ft_token(s + *pos, "ra")
		+ STACK_OP_RB * ft_token(s + *pos, "rb")
		+ STACK_OP_RR * ft_token(s + *pos, "rr")
		+ STACK_OP_RRA * ft_token(s + *pos, "rra")
		+ STACK_OP_RRB * ft_token(s + *pos, "rrb")
		+ STACK_OP_RRR * ft_token(s + *pos, "rrr");

	*pos += 3 + !!(op & __STACK_OP_REV_ROTATE);
	return (op);
}

static char	*read_stdin(size_t *size, t_state *s)
{
	char	*buf;
	char	*tmp;
	size_t	sz;
	ssize_t	ret;

	sz = 1024;
	buf = malloc(sz);
	while (1)
	{
		ret = read(0, buf + sz - 1024, 1024);
		if (ret < 0)
			exit((ft_dprintf(2, "Error\n"), state_free(s), 1));
		if (ret == 0)
		{
			*size = sz - 1024;
			return (buf);
		}
		tmp = malloc(sz + ret + 1024);
		ft_memcpy(tmp, buf, sz - 1024 + ret);
		free(buf);
		buf = tmp;
		sz += ret;
	}
}

int	main(int ac, char **av)
{
	char			*in;
	size_t			size;
	size_t			pos;
	t_state			state;
	enum e_stack_op	o;

	state = parse_args(NULL, ac, av);
	in = read_stdin(&size, &state);
	pos = 0;
	while (pos < size)
	{
		printf("pos=%zu size=%zu\n", pos, size);
		o = parse_op(in, &pos);
		if (!o)
			exit((ft_dprintf(2, "Error1\n"), free(in), state_free(&state), 1));
		op(&state, o);
	}
	free(in);
	if (stack_sorted(&state.sa) && !state.sb.size)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	state_free(&state);
	return (0);
}
