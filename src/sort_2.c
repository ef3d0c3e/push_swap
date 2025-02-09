#include "push_swap.h"
#include "stack.h"

void sort_2(struct s_data *data, struct s_blk *blk)
{
	if (blk->dest & __BLK_BOT || blk->dest == BLK_B_TOP)
	{
	}

	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		move_from_to(data, to_sort->loc, TOP_A);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	if (data->sa.data[0] > data->sa.data[1])
		op(data, STACK_OP_SA);
	blk->size -= 2;
}
