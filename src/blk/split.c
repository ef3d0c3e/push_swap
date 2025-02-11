#include "blk.h"
#include "../state/state.h"
#include "ft_printf.h"
#include "../util.h"

static inline t_split	init_split(const t_blk *blk)
{
	return ((t_split){
		.data = {
			{.size = 0, .dest = (const t_blk_dest[2]){BLK_B_BOT, BLK_B_TOP}
			[blk->dest == BLK_B_BOT]},
		{.size = 0, .dest = (const t_blk_dest[2]){BLK_B_TOP, BLK_A_BOT}
		[(blk->dest & __BLK_SEL) == __BLK_B]},
		{.size = 0, .dest = (const t_blk_dest[2]){BLK_A_TOP, BLK_A_BOT}
		[blk->dest == BLK_A_TOP]},
	}});
}

static inline void check_max(t_state *s, t_blk *blk)
{
	struct s_stack	*st;

	st = &s->sa;
	if (blk->dest == BLK_A_TOP && blk->size == 3)
		return (blk_sort_3(s, blk));
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

static void ps(const char *name, const t_state *s)
{
	ft_printf(" [ STATE: %s ]\n", name);
	ft_printf("OP | ");

	for (size_t i = 0; i < s->op_size; ++i)
		ft_printf(" %s", stack_op_name(s->ops[i]));

	ft_printf("\n A | ");
	for (size_t i = 0; i < s->sa.size; ++i)
		ft_printf(" %d", s->sa.data[i]);
	ft_printf("\n B | ");
	for (size_t i = 0; i < s->sb.size; ++i)
		ft_printf(" %d", s->sb.data[i]);
	ft_printf("\n");
}

t_split blk_split(t_state *s, t_blk *blk, int p1, int p2)
{
	t_split	split;
	int		val;
	//size_t	i;
	
	//state_pivots(s, blk, pivots, pivots + 1);
	//ft_dprintf(2, "pivots=(%d, %d)\n", pivots[0], pivots[1]);
	split = init_split(blk);
	while (blk->size)
	{
		val = blk_value(s, blk, 0);
		if (val >= p2) // max
		{
			blk_move(s, blk->dest, split.data[2].dest);
			++split.data[2].size;
		}
		else if (val >= p1) // mid
		{
			split.data[1].size += (blk_move(s, blk->dest, split.data[1].dest), 1);
		}
		else // min
		{
			split.data[0].size += (blk_move(s, blk->dest, split.data[0].dest), 1);
		}
		--blk->size;
	}
	return (split);
}
