#include "ft_printf.h"
#include "sort.h"
#include "../state/state.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2)
{
	size_t	i;
	float	f[2];

	i = 0;
	while (i++ < blk->size)
		s->tmp_buffer[i - 1] = blk_value(s, blk, i - 1);
    quicksort(s->tmp_buffer, 0, blk->size - 1);
	f[0] = 0.2;
	f[1] = 0.6;
	if (s->annealing_depth < s->pivots->max_anneal)
		annealing_precise(s, blk, f, f + 1);
	else if (s->annealing_depth < s->pivots->max_fast_anneal)
		annealing_fast(s, blk, f, f + 1);
	*p1 = s->tmp_buffer[(int)(f[0] * blk->size)];
	*p2 = s->tmp_buffer[(int)(f[1] * blk->size)];
}
