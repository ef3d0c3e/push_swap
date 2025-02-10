#include "blk.h"
#include "../state.h"
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


t_split blk_split(t_state *s, t_blk *blk)
{
	int	pivots[2];
	t_split	split;
	int		val;
	size_t	i;
	
	state_pivots(s, blk, pivots, pivots + 1);
	split = init_split(blk);
	i = 0;
	while (i++ < blk->size)
	{
		val = blk_value(s, blk, 0);
		if (val > pivots[1]) // max
		{
			blk_move(s, blk->dest, split.data[2].dest);
			check_max(s, &split.data[2]);
			++split.data[2].size;
		}
		else if (val > pivots[0]) // mid
			split.data[1].size += (blk_move(s, blk->dest, split.data[1].dest), 1);
		else // min
			split.data[0].size += (blk_move(s, blk->dest, split.data[0].dest), 1);
	}
	/*
	ft_printf("-- ROLL blocks=(%d, %d, %d)\n", split.data[0].size, split.data[1].size, split.data[2].size);
	i = 1;
	while (i++ < split.data[0].size)
		op(s, STACK_OP_RRR);
	ft_printf("-- ROLL\n");
	*/
	return (split);
}

t_split blk_split_b2a(t_state *s, t_blk *blk)
{
	int	pivots[2];
	t_split	split;
	int		val;
	size_t	i;
	
	state_pivots(s, blk, pivots, pivots + 1);
	split = init_split(blk);
	i = 0;
	while (i++ < blk->size)
	{
		val = blk_value(s, blk, 0);
		if (val > pivots[1]) // max
		{
			split.data[2].size += (blk_move(s, blk->dest, split.data[2].dest), 1);
		}
		else if (val > pivots[0]) // mid
		{
			split.data[1].size += (blk_move(s, blk->dest, split.data[1].dest), 1);
		}
		else // min
		{
			split.data[0].size += (blk_move(s, blk->dest, split.data[0].dest), 1);
		}
	}
	//ft_printf("-- ROLL blocks=(%d, %d, %d)\n", split.data[0].size, split.data[1].size, split.data[2].size);
	//i = 1;
	//while (i++ < split.data[0].size)
	//	op(s, STACK_OP_RRR);
	//ft_printf("-- ROLL\n");
	return (split);
}
