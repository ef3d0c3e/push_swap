#include "../state.h"
#include "../util.h"
#include "opti.h"
#include "backtrack.h"
#include "ft_printf.h"

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
	ft_printf(" [ STATE: %s ]\n", name);
	ft_printf("OP | ");

	for (size_t i = 0; i < s->op_size; ++i)
		ft_printf(" %s", stack_op_name(s->ops[i]));

	ft_printf("\n A | ");
	for (size_t i = 0; i < s->sa.size; ++i)
		ft_printf(" %d", s->sa.data[i]);
	ft_printf("\n B | ");
	for (size_t i = 0; i < s->sb.size; ++i)
		ft_printf(" %d", s->sb.data[i]);
	ft_printf("\n");
}

/* Find a corresponding future state to the current state, returns the number of skipped frames */
static inline size_t find_future(const t_backtrack *bt, const size_t start, const t_state* state)
{
	const t_savestate	*future;
	size_t				i;
	size_t				best;

	i = 1;
	best = 0;
	while (i < bt->max_frame_lookhead && start + i + 1 < bt->saves_size)
	{
		future = bt->saves + start + i;
		if (bt_compare_states(state, future))
			best = i;
		++i;
	}
	return (best);
}

void	state_revert(t_state *s, const t_savestate *ss)
{
	s->sa.size = ss->sa.size;
	s->sb.size = ss->sb.size;
	ft_memcpy(s->sa.data, ss->sa.data, ss->sa.size * sizeof(int));
	ft_memcpy(s->sb.data, ss->sb.data, ss->sb.size * sizeof(int));
}

static void backtrack(t_backtrack *bt, size_t depth, t_state *parent, const size_t skip)
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
		results[i] = find_future(bt, bt->index + skip, parent);
		if (depth < bt->max_insn_recurse)
			backtrack(bt, depth + 1, parent, skip + results[i]);
		state_revert(parent, &parent->saves[depth]);
		++i;
	}

	// find best
	i = 1;
	max = 0;
	while (i < sizeof(op_insns) / sizeof(op_insns[0]))
	{
		if (results[i] > results[max])
		{
			max = i;
		}
		++i;
	}

	if (skip + results[max] > bt->best_skip)
	{
		bt->best_skip = skip + results[max];
		bt->best_len = depth + 1;
		bt->ops[depth] = op_insns[max];
		ft_memcpy(bt->best_ops, bt->ops, bt->best_len * sizeof(enum e_stack_op));
	}
}

static void	init_bt(t_backtrack *bt, const t_state *s)
{
	bt->max_frame_lookhead = 20;
	bt->max_insn_recurse = 1;
	bt->saves = s->saves;
	bt->saves_size = s->saves_size;
}

void	opti(const t_state *s)
{
	size_t	i;
	t_state tmp;
	t_backtrack bt;

			for (size_t j = 0; j < s->sa.size; ++j)
				ft_printf("%d ", s->sa.data[j]);
	size_t cnt = 0;

	i = 0;
	init_bt(&bt, s);
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
				cnt += bt.best_ops[j] != STACK_OP_NOP;
				//ft_printf("|%s\n", stack_op_name(bt.best_ops[j]));
			//ps("before", &tmp);
			//ft_printf("i=%d\n", i);
			//t_state after = state_from_savestate(s->saves + i);
			//ps("after", &after);
			//state_free(&after);
		}
		else
		{
			//ft_printf(">%s\n", stack_op_name(s->ops[i]));
			++cnt;
			++i;
		}
		state_free(&tmp);
	}
	ft_printf("\nreduction = %d\n", cnt);

}
