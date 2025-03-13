/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "args.h"
#include "blk/blk.h"
#include "sort/sort.h"
#include "state/state.h"
#include <stddef.h>
#include <stdio.h>

static int	parse_int_err(const char *s, t_state *st)
{
	size_t	i;
	int		val;
	int		p;

	i = 0;
	val = 0;
	p = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		val = val * 10 + (s[i++] - '0');
		if (val < p)
			exit((dprintf(2, "Error\n"), state_free(st), 1));
		p = val;
	}
	if (s[i])
		exit((dprintf(2, "Error\n"), state_free(st), 1));
	return (val);
}

static int	find(int v, int *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == v)
			return (1);
		++i;
	}
	return (0);
}

t_state	parse_args(const t_pivots_cfg *pivots, int argc, char **argv)
{
	size_t	i;
	int		v;
	t_state	s;

	if (argc < 2)
		exit(0);
	s = state_new(pivots, 0xf6c5d704, argc - 1);
	i = 1;
	while (i < (size_t)argc)
	{
		v = parse_int_err(argv[i++], &s);
		if (find(v, s.sa.data, s.sa.size))
			exit((dprintf(2, "Error\n"), state_free(&s), 1));
		s.sa.data[s.sa.size++] = v;
	}
	return (s);
}
