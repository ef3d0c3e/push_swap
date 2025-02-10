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

const t_stack	*blk_stack(const t_state *s, enum e_blk_dest dest)
{
	if ((dest & __BLK_SEL) == __BLK_A)
		return (&s->sa);
	return (&s->sb);
}

int	blk_abs_sorted(const t_state *s, enum e_blk_dest dest, size_t offset)
{
	const t_blk blk = (t_blk){blk_stack(s, dest)->size, dest};
	size_t		i;
	int			val;


	if (blk.size <= 1 + offset)
		return (1);

	val = blk_value(s, &blk, offset);
	i = offset + 1;
	while (i < blk.size)
	{
		if (blk_value(s, &blk, i) != val + 1)
			return (0);
		val = blk_value(s, &blk, i);
		++i;
	}
	return (1);
}
