/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annealing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sort.h"
#include "../state/state.h"
#include "../util.h"
#include <stdio.h>

/* Minimum of two values */
static inline int	min(int x, int y)
{
	if (y < x)
		return (y);
	return (x);
}

/* Gets a random float within [-1, 1] */
static inline float	get_random_delta(t_state *s)
{
	return (((state_random(s) / (float)UINT32_MAX) - 0.5f) * 2.f);
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
			state->tmp_buffer[min(f2 * blk.size, blk.size - 1)]);
	i = 0;
	while (i++ < 3)
		blk_sort(&clone, &split.data[3 - i]);
	i = clone.op_size;
	state_free(&clone);
	return (i);
}

static void
	annealing_loop(t_state *s, const t_blk *blk, float temp, float *best)
{
	size_t	i;
	float	new[2];
	int		eval;
	int		eval_best;

	i = 0;
	eval_best = 1000000000;
	while (i++ < s->pivots->max_tries)
	{
		new[0] = clamp(best[0] + get_random_delta(s) * s->pivots->factor_step,
				0.f, 1.f);
		new[1] = clamp(best[1] + get_random_delta(s) * s->pivots->factor_step,
				0.f, 1.f);
		if (new[0] == new[1])
			continue ;
		eval = evaluate_pivots(s, *blk, new[0], new[1]);
		if (eval < eval_best || (state_random(s) / (float)UINT32_MAX)
			< approx_exp((eval_best - eval) / temp))
		{
			eval_best = eval;
			best[0] = new[0];
			best[1] = new[1];
		}
	}
}

void	annealing_precise(
	t_state *s,
	const t_blk	*blk,
	float *best_f1,
	float *best_f2)
{
	float	best[2];
	float	temperature;

	best[0] = 0.2;
	best[1] = 0.6;
	temperature = s->pivots->temperature_initial;
	while (temperature > s->pivots->temperature_min / (1 + s->annealing_depth))
	{
		annealing_loop(s, blk, temperature, best);
		temperature *= s->pivots->temperature_cooling;
	}
	*best_f1 = best[0];
	*best_f2 = best[1];
}
