#include "blk.h"
#include "../state/state.h"
#include "../util.h"
#include <stdio.h>

static inline t_split	init_split(const t_blk *blk, float f1, float f2)
{
	return ((t_split){
		.data = {
			{.size = 0, .dest = (const t_blk_dest[2]){BLK_B_BOT, BLK_B_TOP}
			[blk->dest == BLK_B_BOT], .pivots = {f1, f2}},
		{.size = 0, .dest = (const t_blk_dest[2]){BLK_B_TOP, BLK_A_BOT}
		[(blk->dest & __BLK_SEL) == __BLK_B], .pivots = {f1, f2}},
		{.size = 0, .dest = (const t_blk_dest[2]){BLK_A_TOP, BLK_A_BOT}
		[blk->dest == BLK_A_TOP], .pivots = {f1, f2}},
	}});
}

t_split blk_split(t_state *s, t_blk *blk, float f1, float f2)
{
	t_split	split;
	int		val;
	int		p1;
	int		p2;

	p1 = s->tmp_buffer[(int)(f1 * blk->size)];
	p2 = s->tmp_buffer[(int)(f2 * blk->size)];
	split = init_split(blk, f1, f2);
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
			blk_move(s, blk->dest, split.data[1].dest);
			++split.data[1].size;
		}
		else // min
		{
			blk_move(s, blk->dest, split.data[0].dest);
			++split.data[0].size;
		}
		--blk->size;
	}
	return (split);
}
