#include "sort.h"
#include "../state/state.h"

t_pivots_data	pivots_init(struct s_pivots_cfg cfg)
{
	return ((t_pivots_data){
		.cfg = cfg,
		
	});
}

void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2)
{
	float	f[2];

	// TODO
	for (size_t i = 0; i < blk->size; ++i)
		s->tmp_buffer[i] = blk_value(s, blk, i);
    quicksort(s->tmp_buffer, 0, blk->size - 1);

	f[0] = 0.33;
	f[1] = 0.66;
	if (blk->size > 30)
		annealing_precise(s, blk, f, f + 1);

	*p1 = s->tmp_buffer[(int)(blk->size * f[0])];
	*p2 = s->tmp_buffer[(int)(blk->size * f[1])];
}
