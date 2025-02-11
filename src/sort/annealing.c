#include "sort.h"
#include "../state/state.h"
#include <math.h>

// Evaluate the current choice of pivots
static inline int evaluate_pivots(t_state *state, t_blk blk, float f1, float f2) {
	t_state	clone;
	t_split split;
	size_t	i;
	int		p[2];

	p[0] = state->tmp_buffer[(int)(f1 * blk.size)];
	p[1] = state->tmp_buffer[(int)(f2 * blk.size)];

	// Clone state
	clone = state_partial_clone(state);
	split = blk_split(&clone, &blk, p[0], p[1]);

    // Here you would have logic to compute the instruction count for the chosen pivots
    // For simplicity, assume `evaluate` returns a number representing the instruction count

	i = 0;
	while (i < 3)
	{
		//ft_printf("BEGIN REC %d [%d/%d]\n", i, split.data[2 - i].size, split.data[2 - i].dest);
		blk_sort(&clone, &split.data[2 - i]);
		++i;
	}

	i = clone.op_size;
	state_free(&clone);
    return i;  // Placeholder, replace with your actual calculation
}

static inline float	get_delta(t_state *s)
{
	return ((state_random(s) / (float)UINT32_MAX) - 0.5f) * 2.f;
}

void annealing_precise(t_state *s, const t_blk	*blk, float *best_f1, float *best_f2)
{
	float f1 = 0.33f, f2 = 0.66;  // Initial pivots
    int best_eval = evaluate_pivots(s, *blk, f1, f2);  // Initial evaluation
	//ft_printf("start eval=%d\n", best_eval);
    float best_factor1 = f1, best_factor2 = f2;

    float temperature = s->pivots->cfg.temperature_initial;

#pragma omp parallel
    while (temperature > s->pivots->cfg.temperature_min) {
        for (size_t i = 0; i < s->pivots->cfg.max_tries; i++) {
            // Try small random variations
            float delta_f1 = get_delta(s) * s->pivots->cfg.factor_step;
            float delta_f2 = get_delta(s) * s->pivots->cfg.factor_step;

            float new_f1 = best_factor1 + delta_f1;
            float new_f2 = best_factor2 + delta_f2;

            // Ensure factors stay within valid bounds [0.0, 1.0]
            new_f1 = (new_f1 < 0.0f) ? 0.0f : (new_f1 > 1.0f) ? 1.0f : new_f1;
            new_f2 = (new_f2 < 0.0f) ? 0.0f : (new_f2 > 1.0f) ? 1.0f : new_f2;

            // Avoid both pivots being the same
            if (new_f1 == new_f2) continue;

            // Evaluate the new factor pair
            int new_eval = evaluate_pivots(s, *blk, new_f1, new_f2);
			//ft_printf("new eval [%d]=%d\n", i, new_eval);

            // Decide whether to accept the new solution
            if (new_eval < best_eval) {
                best_eval = new_eval;
                best_factor1 = new_f1;
                best_factor2 = new_f2;
            } else {
                // Accept worse solutions with a certain probability
                float acceptance_prob = exp((best_eval - new_eval) / temperature);
                if ((state_random(s) / (float)UINT32_MAX) < acceptance_prob) {
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
