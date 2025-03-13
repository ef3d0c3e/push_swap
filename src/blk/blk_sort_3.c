/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blk_sort_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "blk.h"
#include "../util.h"

static inline void	sort_3_ta(t_state *s, const int u, const int v, const int w)
{
	((void)(
		(u > v && v > w && (op(s, STACK_OP_SA), op(s, STACK_OP_RA),
				op(s, STACK_OP_SA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_SA), op(s, STACK_OP_RA),
				op(s, STACK_OP_SA), op(s, STACK_OP_RRA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_RA), op(s, STACK_OP_SA),
				op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_RA), op(s, STACK_OP_SA),
				op(s, STACK_OP_RRA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_SA), 1))
		|| (w > v && v > u && (1))));
}

static inline void	sort_3_tb(t_state *s, const int u, const int v, const int w)
{
	((void)(
		(u > v && v > w && (op(s, STACK_OP_PA), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_PA), op(s, STACK_OP_SB),
				op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_SB), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_SB), op(s, STACK_OP_PA),
				op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_PA), op(s, STACK_OP_SB),
				op(s, STACK_OP_PA), op(s, STACK_OP_SA), op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_SB), op(s, STACK_OP_PA),
				op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_SA),
				op(s, STACK_OP_PA), 1))));
}

static inline void	sort_3_ba(t_state *s, const int u, const int v, const int w)
{
	((void)(
		(u > v && v > w && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA),
				op(s, STACK_OP_RRA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA),
				op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA),
				op(s, STACK_OP_SA), op(s, STACK_OP_RRA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA),
				op(s, STACK_OP_SA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA),
				op(s, STACK_OP_PB), op(s, STACK_OP_RRA), op(s, STACK_OP_SA),
				op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_RRA), op(s, STACK_OP_PB),
				op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA),
				op(s, STACK_OP_PA), 1))));
}

static inline void	sort_3_bb(t_state *s, const int u, const int v, const int w)
{
	((void)(
		(u > v && v > w && (op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_RRB),
				op(s, STACK_OP_PA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB),
				op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_RRB),
				op(s, STACK_OP_PA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB),
				op(s, STACK_OP_PA), op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB),
				op(s, STACK_OP_SB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB),
				op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA),
				op(s, STACK_OP_PA), 1))));
}

void	blk_sort_3(t_state *s, t_blk *blk)
{
	const int	u = blk_value(s, blk, 0);
	const int	v = blk_value(s, blk, 1);
	const int	w = blk_value(s, blk, 2);

	if (blk->dest == BLK_A_TOP)
		sort_3_ta(s, u, v, w);
	else if (blk->dest == BLK_B_TOP)
		sort_3_tb(s, u, v, w);
	else if (blk->dest == BLK_A_BOT)
		sort_3_ba(s, u, v, w);
	else
		sort_3_bb(s, u, v, w);
	blk->dest = BLK_A_TOP;
	blk->size -= 3;
}
