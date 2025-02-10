#include "blk.h"
#include "../state.h"

int	blk_value(const t_state *s, const t_blk *blk, size_t pos)
{
	if (blk->dest == BLK_A_TOP)
		return (s->sa.data[pos]);
	else if (blk->dest == BLK_A_BOT)
		return (s->sa.data[s->sa.size - pos - 1]);
	else if (blk->dest == BLK_B_TOP)
		return (s->sb.data[pos]);
	else
		return (s->sb.data[s->sb.size - pos - 1]);
}

int	blk_max(const t_state *s, const t_blk *blk)
{
	int		max;
	int		val;
	size_t	i;

	max = -1;
	i = 0;
	while (i != blk->size)
	{
		val = blk_value(s, blk, i);
		if (val > max)
			max = val;
		++i;
	}
	return(max);
}
