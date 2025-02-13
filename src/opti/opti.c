#include "../state/state.h"
#include "../util.h"
#include "opti.h"
#include "backtrack.h"
#include "ft_printf.h"
#include <stdio.h>

static enum e_stack_op op_insns[] = {
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

static void ps(const char *name, const t_state *s)
{
	ft_dprintf(2, " [ STATE: %s ]\n", name);
	ft_dprintf(2, "OP | ");

	for (size_t i = 0; i < s->op_size; ++i)
		ft_dprintf(2, " %s", stack_op_name(s->ops[i]));

	ft_dprintf(2, "\n A | ");
	for (size_t i = 0; i < s->sa.size; ++i)
		ft_dprintf(2, " %d", s->sa.data[i]);
	ft_dprintf(2, "\n B | ");
	for (size_t i = 0; i < s->sb.size; ++i)
		ft_dprintf(2, " %d", s->sb.data[i]);
	ft_dprintf(2, "\n");
}

static void	backtrack(
		t_backtrack *bt,
		size_t depth,
		t_state *parent,
		const size_t skip
		)
{
	ssize_t				results[sizeof(op_insns) / sizeof(op_insns[0])];
	size_t				i;
	size_t				max;

	i = 0;
	state_create_savestate(parent);
	while (i < sizeof(op_insns) / sizeof(op_insns[0]))
	{
		bt->ops[depth] = op_insns[i];
		stack_op(&parent->sa, &parent->sb, bt->ops[depth]);
		results[i] = bt_find_future(bt, bt->index + skip, parent);
		if (depth < bt->cfg.max_insn_recurse)
			backtrack(bt, depth + 1, parent, skip + results[i]);
		state_revert(parent, &parent->saves[depth]);
		++i;
	}
	(void)((i = 1), max = 0);
	while (i < sizeof(op_insns) / sizeof(op_insns[0]))
		if (results[i++] > results[max])
			max = i - 1;
	if (skip + results[max] > bt->best_skip)
	{
		bt->best_skip = skip + results[max];
		bt->best_len = depth + 1;
		bt->ops[depth] = op_insns[max];
		ft_memcpy(bt->best_ops, bt->ops, bt->best_len * sizeof(enum e_stack_op));
	}
}

void	opti(const t_state *s, const t_optimizer_cfg cfg)
{
	size_t		i;
	t_state		tmp;
	t_backtrack bt;
	t_state		sim;

	i = 0;
	sim = state_from_savestate(&s->saves[0]);
	bt.cfg = cfg;
	bt.saves = s->saves;
	bt.saves_size = s->saves_size;
	printf("SS=%zu\n", s->saves_size);
	while (i < s->op_size)
	{
		bt.best_len = 0;
		bt.best_skip = 0;
		bt.index = i;
		tmp = state_from_savestate(bt.saves + i);
		backtrack(&bt, 0, &tmp, 0);
		//ft_printf("BEST [at %d]: len=%d skip=%d\n", i, bt.best_len, bt.best_skip);

		if (bt.best_skip > 1)
		{
			i += bt.best_skip;
			for (size_t j = 0; j < bt.best_len; ++j)
			{
				if (bt.best_ops[j] != STACK_OP_NOP)
					op(&sim, bt.best_ops[j]);
			}
		}
		else
		{
			op(&sim, s->ops[i]);
			++i;
		}
		state_free(&tmp);
	}
	ft_printf("After opti: %d\n", sim.op_size);
	//state_dump(&sim);
	state_free(&sim);
}
