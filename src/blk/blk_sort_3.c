#include "blk.h"
#include "../util.h"
#include "ft_printf.h"

static inline void encode(t_state *state, enum e_stack_op o, t_blk *blk)
{
	op(state, ((o & __STACK_OPERATOR)
				| __STACK_OP_SEL_A * ((blk->dest & __BLK_SEL) == __BLK_A)
				| __STACK_OP_SEL_B * ((blk->dest & __BLK_SEL) == __BLK_B)));
}

void blk_sort_3_top_for_a(t_state *s, t_blk *blk)
{
	const int	u = blk_value(s, blk, 0);
	const int	v = blk_value(s, blk, 1);
	const int	w = blk_value(s, blk, 2);

	if ((blk->dest & __BLK_POS) == __BLK_TOP)
	{
		//asm("int $3");
		ft_printf("(%d, %d, %d, %d)\n", u, v, w, blk->dest);
		((void)((u > v && v > w
				&& (encode(s, __STACK_OP_ROTATE, blk),
					encode(s, __STACK_OP_SWAP, blk), 1))
			|| (u > w && w > v
				&& (encode(s, __STACK_OP_ROTATE, blk), 1))
			|| (v > u && u > w
				&& (encode(s, __STACK_OP_REV_ROTATE, blk), 1))
			|| (v > w && w > u
				&& (encode(s, __STACK_OP_SWAP, blk),
					encode(s, __STACK_OP_ROTATE, blk), 1))
			|| (w > u && u > v
				&& (encode(s, __STACK_OP_SWAP, blk), 1))));
	}
	else { /* TODO */ }
}

void blk_sort_3(t_state *s, t_blk *blk)
{
	const int	u = blk_value(s, blk, 0);
	const int	v = blk_value(s, blk, 1);
	const int	w = blk_value(s, blk, 2);

	if (blk->dest == BLK_A_TOP)
		blk_sort_3_top_for_a(s, blk);
	else if (blk->dest == BLK_B_TOP)
		((void)(
		   (u > v && v > w && (op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_PA), op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_PA), op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_SA), op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_SB), op(s, STACK_OP_PA), op(s, STACK_OP_SA), op(s, STACK_OP_PA), 1))
	));
	else if (blk->dest == BLK_A_BOT)
		((void)(
		   (u > v && v > w && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), op(s, STACK_OP_RRA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_PB), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_RRA), op(s, STACK_OP_PB), op(s, STACK_OP_RRA), op(s, STACK_OP_RRA), op(s, STACK_OP_SA), op(s, STACK_OP_PA), 1))
	));
	else
		((void)(
		   (u > v && v > w && (op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), 1))
		|| (u > w && w > v && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_SA), 1))
		|| (v > u && u > w && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), 1))
		|| (v > w && w > u && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (w > u && u > v && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_SB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
		|| (w > v && v > u && (op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_RRB), op(s, STACK_OP_PA), op(s, STACK_OP_PA), op(s, STACK_OP_PA), 1))
	));

	blk->dest = BLK_A_TOP/* * (blk->dest != BLK_B_BOT)
		+ BLK_B_TOP * (blk->dest == BLK_B_BOT)*/;
	blk->size -= 3;
}
