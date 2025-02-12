#include "push_swap.h"
#include "blk/blk.h"
#include "sort/sort.h"
#include "stack/stack.h"
#include "opti/opti.h"
#include "state/state.h"

#include <ft_printf.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <omp.h>

/* Evaluate the score of a pivot */
static inline int	evaluate_pivots(
		t_state *state,
		t_blk blk,
		float f1,
		float f2
		)
{
	t_state	clone;
	t_split	split;
	size_t	i;

	clone = state_partial_clone(state);
	++clone.annealing_depth;
	split = blk_split(&clone, &blk, state->tmp_buffer[(int)(f1 * blk.size)],
			state->tmp_buffer[(int)(f2 * blk.size)]);
	i = 0;
	while (i++ < 3)
		blk_sort(&clone, &split.data[3 - i]);
	i = clone.op_size;
	state_free(&clone);
	return (i);
}

int main(int ac, char **av)
{
	const t_pivots_cfg pivots = (t_pivots_cfg) {
		.temperature_initial = 1.0f,
		.temperature_min = .1f,
		.temperature_cooling = .85f,
		.factor_step = 0.1f,
		.max_tries = 5,
		.max_anneal = 0,
		.max_fast_anneal = 0,
	};
	t_state			state;
	size_t			i;

	if (ac == 1)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}

	state = state_new(&pivots, 0xf6c5d704, ac - 1);
	i = 1;
	while (i < (size_t)ac)
		state.sa.data[state.sa.size++] = atoi(av[i++]);

	t_blk blk = {.size = state.sa.size, .dest = BLK_A_TOP};
	for (size_t i = 0; i < blk.size; ++i)
		state.tmp_buffer[i] = blk_value(&state, &blk, i);
	quicksort(state.tmp_buffer, 0, blk.size - 1);

	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel
	for (float f1 = 0.f; f1 <= 1.f; f1 += .01f)
	{
		for (float f2 = f1; f2 <= 1.f; f2 += .01f)
		{
			size_t cost = evaluate_pivots(&state, blk, f1, f2);
			omp_set_lock(&lock);
			printf("%f %f %zu\n", f1, f2, cost);
			omp_unset_lock(&lock);
		}
	}
	omp_destroy_lock(&lock);

	state_free(&state);

	return 0;
}
