#include "ft_printf.h"
#include "sort.h"
#include "../state/state.h"
#include <stdint.h>
#include <stdio.h>

static inline uint32_t	murmur3_32(const uint8_t *key, size_t len, uint32_t seed) {
    uint32_t	h;
	size_t		i;

	h = seed;
	i = 0;
	while (i < len)
	{
        h ^= key[i++];
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return (h);
}

static inline uint32_t	histogram_hash(const t_state *s, const t_blk *blk) {
    int		hist[16] = {0};  // Divide into 16 buckets
	size_t	i;

	i = 0;
	while (i < blk->size)
        hist[(size_t)((float)blk_value(s, blk, i++) / (float)s->sa.capacity * 16.f)]++;  // Bin into buckets
    return murmur3_32((const uint8_t *)hist, sizeof(hist), 0x49432a43);  // Hash the histogram
}

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
