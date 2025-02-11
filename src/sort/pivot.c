#include "sort.h"
#include "../state/state.h"

#include <math.h>

t_pivots_data	pivots_init(struct s_pivots_cfg cfg)
{
	return ((t_pivots_data){
		.cfg = cfg,
		
		});
}

static uint32_t	xorshift32(t_state *s)
{
    uint32_t	x;
    uint32_t	tmp;

	x = s->seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
	tmp = s->seed;
	s->seed = x;
    return (tmp);
}
// Evaluate the current choice of pivots
static int evaluate_pivots(const t_state *state, t_blk blk, float f1, float f2) {
	t_state	clone;
	size_t	i;
	int		p1;
	int		p2;

	p1 = state->tmp_buffer[(int)(f1 * blk.size)];
	p2 = state->tmp_buffer[(int)(f2 * blk.size)];

	// Clone state
	clone = state_partial_clone(state);
	

    // Here you would have logic to compute the instruction count for the chosen pivots
    // For simplicity, assume `evaluate` returns a number representing the instruction count
	

	i = 0;
	while (i < 3)
	{
		//ft_printf("BEGIN REC %d [%d/%d]\n", i, split.data[2 - i].size, split.data[2 - i].dest);
		blk_sort(&clone, &blk);
		++i;
	}

	i = clone.op_size;
	state_free(&clone);
    return i;  // Placeholder, replace with your actual calculation
}

static void simulated_annealing(t_state *s, const t_blk	*blk, float *best_f1, float *best_f2)
{
	float f1 = 0.33f, f2 = 0.33f;  // Initial pivots
    int best_eval = evaluate_pivots(s, *blk, f1, f2);  // Initial evaluation
    float best_factor1 = f1, best_factor2 = f2;

    float temperature = s->pivots->cfg.temperature_initial;

    while (temperature > s->pivots->cfg.temperature_min) {
        for (size_t i = 0; i < s->pivots->cfg.max_tries; i++) {
            // Try small random variations
            float delta_f1 = (xorshift32(s) / (float)UINT32_MAX) * s->pivots->cfg.factor_step * 2 - s->pivots->cfg.factor_step;
            float delta_f2 = (xorshift32(s) / (float)UINT32_MAX) * s->pivots->cfg.factor_step * 2 - s->pivots->cfg.factor_step;

            float new_f1 = best_factor1 + delta_f1;
            float new_f2 = best_factor2 + delta_f2;

            // Ensure factors stay within valid bounds [0.0, 1.0]
            new_f1 = (new_f1 < 0.0f) ? 0.0f : (new_f1 > 1.0f) ? 1.0f : new_f1;
            new_f2 = (new_f2 < 0.0f) ? 0.0f : (new_f2 > 1.0f) ? 1.0f : new_f2;

            // Avoid both pivots being the same
            if (new_f1 == new_f2) continue;

            // Evaluate the new factor pair
            int new_eval = evaluate_pivots(s, *blk, new_f1, new_f2);

            // Decide whether to accept the new solution
            if (new_eval < best_eval) {
                best_eval = new_eval;
                best_factor1 = new_f1;
                best_factor2 = new_f2;
            } else {
                // Accept worse solutions with a certain probability
                float acceptance_prob = exp((best_eval - new_eval) / temperature);
                if ((xorshift32(s) / (float)UINT32_MAX) < acceptance_prob) {
                    best_eval = new_eval;
                    best_factor1 = new_f1;
                    best_factor2 = new_f2;
                }
            }
        }

        // Cool down the temperature
        temperature *= s->pivots->cfg.temperature_cooling;
    }

    *best_f1 = best_factor1;
    *best_f2 = best_factor2;
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void	pivots_next(t_state *s, const t_blk	*blk, int *p1, int *p2)
{
	float	f1;
	float	f2;

	// TODO
	for (size_t i = 0; i < blk->size; ++i)
		s->tmp_buffer[i] = blk_value(s, blk, i);
    qsort(s->tmp_buffer, blk->size, sizeof(int), cmp);

	f1 = 0.33;
	f2 = 0.66;
	//simulated_annealing(s, blk, &f1, &f2);

	*p1 = s->tmp_buffer[(int)(blk->size * f1)];
	*p2 = s->tmp_buffer[(int)(blk->size * f2)];
}
