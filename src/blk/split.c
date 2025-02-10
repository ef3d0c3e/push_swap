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
	//size_t	i;
	
	state_pivots(s, blk, pivots, pivots + 1);
	//ft_dprintf(2, "pivots=(%d, %d)\n", pivots[0], pivots[1]);
	split = init_split(blk);
	while (blk->size)
	{
		val = blk_value(s, blk, 0);
		if (val > pivots[1]) // max
		{
			blk_move(s, blk->dest, split.data[2].dest);
			++split.data[2].size;
			//check_max(s, &split.data[2]);
		}
		else if (val > pivots[0]) // mid
			split.data[1].size += (blk_move(s, blk->dest, split.data[1].dest), 1);
		else // min
			split.data[0].size += (blk_move(s, blk->dest, split.data[0].dest), 1);
		--blk->size;
	}
	//asm("int $3");
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
	return (split);
}
