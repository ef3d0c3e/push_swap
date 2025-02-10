#include "blk.h"
#include "../state.h"

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

void	blk_quartiles(const t_state *s, const t_blk *blk, int *q1, int *q3)
{
	int		max;
	size_t	i;
	int		largest;
	int		stop;

	*q3 = blk->size / 3;
	*q1 = *q3 + *q3;

	max = blk_max(s, blk);
	largest = -1;
	stop = 0;
	while (!stop)
	{
		i = 0;
		largest = -1;
		while (i < blk->size)
		{
			if (blk_value(s, blk, i) == max)
			{
				--*q3;
				--*q1;

				if (!*q3)
				{
					*q3 = max;
					stop = 1;
				}
			}
			else if (blk_value(s, blk, i) > largest && blk_value(s, blk, i) < max)
				largest = blk_value(s, blk, i);

			++i;
		}
		max = largest;
	}

	stop = 0;
	while (!stop)
	{
		i = 0;
		largest = -1;
		while (i < blk->size)
		{
			if (blk_value(s, blk, i) == max)
			{
				--*q1;

				if (!*q1)
				{
					*q1 = max;
					stop = 1;
				}
			}
			else if (blk_value(s, blk, i) > largest && blk_value(s, blk, i) < max)
				largest = blk_value(s, blk, i);

			++i;
		}
		max = largest;
	}
}
