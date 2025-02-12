#include "ft_printf.h"
#include "sort.h"
#include "../state/state.h"
#include <stdint.h>
#include <stdio.h>

void	pivots_next(t_state *s, const t_blk	*blk, float *p1, float *p2)
{
	for (size_t i = 0; i < blk->size; ++i)
		s->tmp_buffer[i] = blk_value(s, blk, i);
    quicksort(s->tmp_buffer, 0, blk->size - 1);

//printf("hash: [%zu] %x\n", blk->size, histogram_hash(s, blk));
	*p1 = 0.33;
	*p2 = 0.66;
	//if (s->annealing_depth < s->pivots->max_anneal)
	//	annealing_precise(s, blk, f, f + 1);
	////else if (s->annealing_depth < 2 * s->pivots->max_anneal)
	//else if (blk->size >= 10)
	//annealing_fast(s, blk, p1, p2);
}
