#include "blk.h"
#include "../state.h"

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

t_split blk_split(t_state *state, t_blk blk)
{
	size_t	pivots[2];
	
	state_pivots(state, blk, pivots, pivots + 1);
}
