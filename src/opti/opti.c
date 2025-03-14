/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../state/state.h"
#include "../util.h"
#include "opti.h"
#include "backtrack.h"

/* Get operation from id */
static enum e_stack_op	op_insn(size_t i)
{
	static enum e_stack_op	op_insns[12] = {
		STACK_OP_NOP,
		STACK_OP_SA,
		STACK_OP_SB,
		STACK_OP_SS,
		STACK_OP_PA,
		STACK_OP_PB,
		STACK_OP_RA,
		STACK_OP_RB,
		STACK_OP_RR,
		STACK_OP_RRA,
		STACK_OP_RRB,
		STACK_OP_RRR,
	};

	return (op_insns[i]);
}

static inline void	backtrack(
		t_backtrack *bt,
		size_t depth,
		t_state *parent,
		const size_t skip
		)
{
	ssize_t				results[12];
	size_t				i;
	size_t				max;

	i = 0;
	state_create_savestate(parent);
	while (i < 12)
	{
		bt->ops[depth] = op_insn(i);
		stack_op(&parent->sa, &parent->sb, bt->ops[depth]);
		results[i] = bt_find_future(bt, bt->index + skip, parent);
		if (depth < bt->cfg.max_insn_recurse)
			backtrack(bt, depth + 1, parent, skip + results[i]);
		state_revert(parent, &parent->saves[depth]);
		++i;
	}
	(void)((i = 1), max = 0);
	while (i++ < 12)
		max += (i - 1 - max) * (results[i - 1] > results[max]);
	if (skip + results[max] <= bt->best_skip)
		return ;
	bt->best_skip = skip + results[max];
	bt->best_len = depth + 1;
	bt->ops[depth] = op_insn(max);
	ft_memcpy(bt->best_ops, bt->ops, bt->best_len * sizeof(enum e_stack_op));
}

static inline size_t
	opti_loop(const t_state *s, t_state *sim, t_backtrack *bt, size_t i)
{
	t_state	tmp;
	size_t	j;
	size_t	k;

	bt->best_len = 0;
	bt->best_skip = 0;
	bt->index = i;
	k = i;
	tmp = state_from_savestate(bt->saves + i);
	backtrack(bt, 0, &tmp, 0);
	if (bt->best_skip > 1)
	{
		i += bt->best_skip;
		j = 0;
		while (j < bt->best_len)
		{
			if (bt->best_ops[j] != STACK_OP_NOP)
				op(sim, bt->best_ops[j]);
			++j;
		}
	}
	else
		op(sim, s->ops[i++]);
	state_free(&tmp);
	return (i - k);
}

void	opti(const t_state *s, const t_optimizer_cfg cfg)
{
	size_t		i;
	t_backtrack	bt;
	t_state		sim;

	i = 0;
	sim = state_from_savestate(&s->saves[0]);
	bt.cfg = cfg;
	bt.saves = s->saves;
	bt.saves_size = s->saves_size;
	while (i < s->op_size)
		i += opti_loop(s, &sim, &bt, i);
	state_dump(&sim);
	state_free(&sim);
}
