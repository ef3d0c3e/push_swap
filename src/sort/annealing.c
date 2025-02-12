#include "sort.h"
#include "../state/state.h"
#include <math.h>
#include <stdio.h>

/* Gets a random float within [-1, 1] */
static inline float	get_random_delta(t_state *s)
{
	return ((state_random(s) / (float)UINT32_MAX) - 0.5f) * 2.f;
}

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

void	annealing_precise(t_state *s, const t_blk	*blk, float *best_f1, float *best_f2)
{
	float f1 = 0.33f, f2 = 0.66;  // Initial pivots
    int best_eval = evaluate_pivots(s, *blk, f1, f2);  // Initial evaluation
	//ft_printf("start eval=%d\n", best_eval);
    float best_factor1 = f1, best_factor2 = f2;

    float temperature = s->pivots->temperature_initial;

    while (temperature > s->pivots->temperature_min) {
        for (size_t i = 0; i < s->pivots->max_tries; i++) {
            // Try small random variations
            float delta_f1 = get_random_delta(s) * s->pivots->factor_step;
            float delta_f2 = get_random_delta(s) * s->pivots->factor_step;

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
        temperature *= s->pivots->temperature_cooling;
    }

    *best_f1 = best_factor1;
    *best_f2 = best_factor2;
}

void	annealing_fast(t_state *s, const t_blk	*blk, float *f1, float *f2)
{
	static const float	pivots[][2] = {{.25f, .50f}, {.25f, .66f},
	{.25f, .75f}, {.33f, .50f}, {.33f, .66f}, {.33f, .75f}, {.50f, .66f},
	{.50f, .75f}, {.66f, .75f}};
	size_t				best[2];
	size_t				score;
	size_t				i;

	best[0] = 0;
	best[1] = evaluate_pivots(s, *blk, pivots[0][0], pivots[0][1]);
	i = 1;
	while (i < sizeof(pivots) / sizeof(pivots[0]))
	{
		score = evaluate_pivots(s, *blk, pivots[i][0], pivots[i][1]);
		if (score < best[1])
		{
			best[0] = i;
			best[1] = score;
		}
		++i;
	}
	*f1 = pivots[best[0]][0];
	*f2 = pivots[best[0]][1];
}
