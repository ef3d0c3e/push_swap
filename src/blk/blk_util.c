#include "blk.h"
#include "../state/state.h"

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
