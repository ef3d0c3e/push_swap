#include "blk.h"
#include "../util.h"
#include <ft_printf.h>

void	blk_sort_2(t_state *state, t_blk *blk)
{
	const int u = blk_value(state, blk, 0);
	const int v = blk_value(state, blk, 1);

	if (blk->dest == BLK_A_TOP)
	{
		if (u > v)
			op(state, STACK_OP_SA);
	}
	else if (blk->dest == BLK_A_BOT)
	{
		op(state, STACK_OP_RRA);
		op(state, STACK_OP_RRA);
		if (u < v)
			op(state, STACK_OP_SA);
	}
	else if (blk->dest == BLK_B_TOP)
	{
		if (u < v)
			op(state, STACK_OP_SB);
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
	}
	else
	{
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
		if (u > v)
			op(state, STACK_OP_SA);
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
	{
		blk_sort_2(state, blk);
	}
	else if (blk->size == 3)
	{
		blk_sort_3(state, blk);
	}
}

static inline void pre_sort(t_state *s, t_blk *blk)
{
	while (blk->dest != BLK_A_TOP && blk->size)
	{
		if (s->sa.data[0] == blk_value(s, blk, 0) + 1)
		{
			blk_move(s, blk->dest, BLK_A_TOP);
			--blk->size;
		}
		else if (blk->size >= 2 && s->sa.data[0] == blk_value(s, blk, 1) + 1)
		{
			if (blk->dest == BLK_A_BOT)
			{
				op(s, STACK_OP_RRA);
				op(s, STACK_OP_RRA);
				op(s, STACK_OP_SA);
				if (s->sa.data[1] == s->sa.data[0] + 1)
					--blk->size;
				else
					op(s, STACK_OP_RA);
			}
			else if (blk->dest == BLK_B_TOP)
			{
				op(s, STACK_OP_SB);
				op(s, STACK_OP_PA);
				if (s->sa.data[0] == s->sb.data[0] + 1)
				{
					op(s, STACK_OP_PA);
					--blk->size;
				}
			}
			else if (blk->dest == BLK_B_BOT)
			{
				op(s, STACK_OP_RRB);
				op(s, STACK_OP_RRB);
				op(s, STACK_OP_PA);
				if (s->sa.data[0] == s->sb.data[0] + 1)
				{
					op(s, STACK_OP_PA);
					--blk->size;
				}
				else
					op(s, STACK_OP_RB);
			}
			--blk->size;
		}
		else
			break;
	}
}

void blk_sort(t_state *s, t_blk *blk)
{
	t_split	split;
	size_t	i;

	if (blk->dest == BLK_A_BOT && s->sa.size == blk->size)
		blk->dest = BLK_A_TOP;
	else if (blk->dest == BLK_B_BOT && s->sb.size == blk->size)
		blk->dest = BLK_B_TOP;

	pre_sort(s, blk);
	if (blk->size <= 3)
	{
		ft_printf(">sort_small():\n");
		blk_sort_small(s, blk);
		return;
	}
	split = blk_split(s, blk);
	ft_printf("SPLIT (%d, %d, %d)\n", split.data[0].size, split.data[1].size, split.data[2].size);

	i = 0;
	while (i < 3)
	{
		ft_printf("BEGIN REC %d [%d/%d]\n", i, split.data[2 - i].size, split.data[2 - i].dest);
		blk_sort(s, &split.data[2 - i]);
		++i;
	}
}
