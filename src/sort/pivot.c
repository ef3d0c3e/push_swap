/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sort.h"
#include "../state/state.h"

void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2)
{
	size_t	i;
	float	f[2];

	i = 0;
	while (i++ < blk->size)
		s->tmp_buffer[i - 1] = blk_value(s, blk, i - 1);
	quicksort(s->tmp_buffer, 0, blk->size - 1);
	f[0] = 0.2;
	f[1] = 0.6;
	if (s->annealing_depth < s->pivots->max_anneal)
		annealing_precise(s, blk, f, f + 1);
	*p1 = s->tmp_buffer[(int)(f[0] * (blk->size - 1))];
	*p2 = s->tmp_buffer[(int)(f[1] * (blk->size - 1))];
}
