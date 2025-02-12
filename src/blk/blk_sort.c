#include "blk.h"
#include "../util.h"

void	blk_sort_2(t_state *state, t_blk *blk)
{
	const int	u = blk_value(state, blk, 0);
	const int	v = blk_value(state, blk, 1);

	if (blk->dest == BLK_A_TOP)
		(void)(u > v && (op(state, STACK_OP_SA), 1));
	else if (blk->dest == BLK_A_BOT)
	{
		(void)(op(state, STACK_OP_RRA), op(state, STACK_OP_RRA));
		(void)(u < v && (op(state, STACK_OP_SA), 1));
	}
	else if (blk->dest == BLK_B_TOP)
	{
		(void)(u < v && (op(state, STACK_OP_SB), 1));
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
	}
	else
	{
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
		(void)(u > v && (op(state, STACK_OP_SA), 1));
	}
	blk->size -= 2;
}

void	blk_sort_small(t_state *state, t_blk *blk)
{
	if (blk->size == 1)
	{
		blk_move(state, blk->dest, BLK_A_TOP);
		blk->size -= 1;
	}
	else if (blk->size == 2)
		blk_sort_2(state, blk);
	else if (blk->size == 3)
		blk_sort_3(state, blk);
}

void	blk_sort(t_state *s, t_blk *blk)
{
	t_split	split;
	size_t	i;
	float	pivots[2];

	if (blk->dest == BLK_A_BOT && s->sa.size == blk->size)
		blk->dest = BLK_A_TOP;
	else if (blk->dest == BLK_B_BOT && s->sb.size == blk->size)
		blk->dest = BLK_B_TOP;
	if (blk->size <= 3)
		return (blk_sort_small(s, blk));
	pivots_next(s, blk, pivots, pivots + 1);
	split = blk_split(s, blk, pivots[0], pivots[1]);
	i = 0;
	while (i < 3)
	{
		blk_sort(s, &split.data[2 - i]);
		++i;
	}
}
