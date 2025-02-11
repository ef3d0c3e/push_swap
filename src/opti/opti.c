#include "../state.h"
#include "../util.h"
#include "ft_printf.h"

int	compare_states(const t_state *sim, const t_savestate *orig)
{
	size_t	i;
	
	if (sim->sa.size != orig->sa.size || sim->sb.size != orig->sb.size)
		return (0);
	i = 0;
	while (i < sim->sa.size)
	{
		if (sim->sa.data[i] != orig->sa.data[i])
			return (0);
		++i;
	}
	i = 0;
	while (i < sim->sb.size)
	{
		if (sim->sb.data[i] != orig->sb.data[i])
			return (0);
		++i;
	}
	return (1);
}

static enum e_stack_op op_insns[] = {
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

typedef struct s_backtrack {
	const t_savestate	*saves;
	size_t		saves_size;
	size_t		index;

	size_t				best_len;
	size_t				best_skip;
	enum e_stack_op		best_ops[6];
	enum e_stack_op		ops[6];
}	t_backtrack;

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
static size_t find_future(const t_backtrack *bt, size_t depth, const t_state* state)
{
	const t_savestate	*future;
	size_t				i;
	size_t				best;

	i = 1;
	best = 0;
	//ft_printf("--- $ Search for $ ---\n");
	//ps("temp", state);
	// Look ahead 10
	while (i < 20 && bt->index + i + depth < bt->saves_size)
	{
		future = bt->saves + bt->index + i + depth;
		if (compare_states(state, future))
			best = i;
		++i;
	}
	return (best);
}

static void backtrack(t_backtrack *bt, size_t depth, t_state *parent, const size_t skip)
{
	ssize_t	results[sizeof(op_insns) / sizeof(op_insns[0])];
	size_t	i;
	size_t	val;
	t_state temp;


	i = 0;
	while (i < sizeof(op_insns) / sizeof(op_insns[0]))
	{
		// TODO: Undo
		temp = state_partial_clone(parent);
		bt->ops[depth] = op_insns[i];
		op(&temp, bt->ops[depth]);
		val = find_future(bt, depth, &temp);
		results[i] = val - depth - 1;
		if (results[i] < 0)
			results[i] = 0;
		if (depth < 2)
		{
			if (results[i])
			{
				t_state cpy = state_from_savestate(bt->saves + bt->index + val);
				backtrack(bt, depth + 1, &cpy, skip + results[i]);
				state_free(&cpy);
			}
			else
			backtrack(bt, depth + 1, &temp, skip + results[i]);
		}
		state_free(&temp);
		++i;
	}

	// find best
	i = 1;
	val = 0;
	bt->ops[depth] = op_insns[0];
	while (i < sizeof(op_insns) / sizeof(op_insns[0]))
	{
		if (results[i] > results[val])
		{
			val = i;
		}
		++i;
	}

				ft_printf("bo=%d: %d [%d]\n", depth, results[val], skip);
	if (skip + results[val] > bt->best_skip)
	{
		bt->best_skip = skip + results[val];
		bt->best_len = depth;
		ft_memcpy(bt->best_ops, bt->ops, depth * sizeof(enum e_stack_op));
	}
}

void	opti(const t_state *s)
{
	size_t	i;
	t_state tmp;
	t_backtrack bt;

	i = 0;
	while (i < s->op_size)
	{
		tmp = state_from_savestate(s->saves + i);
		bt.saves = s->saves;
		bt.saves_size = s->saves_size;
		bt.index = i;
		bt.best_len = 0;
		bt.best_skip = 0;
		backtrack(&bt, 0, &tmp, 0);
		ft_printf("BEST [%d]: %d, %d\n", i, bt.best_len, bt.best_skip);
		if (bt.best_skip != 0)
		{
			for (size_t j = 0; j < bt.best_len; ++j)
				ft_printf("%s\n", stack_op_name(bt.best_ops[j]));
			i += bt.best_skip - 1;
			ps("before", &tmp);
			ft_printf("i=%d\n", i);
			t_state after = state_from_savestate(s->saves + i);
			ps("after", &after);
		}
		else
		{
			ft_printf("%s\n", stack_op_name(s->ops[i]));
			++i;
		}
		state_free(&tmp);
		

		/*
		j = 1;
		while (j < 10 && i + j < s->saves_size)
		{
			if (compare_states(&s->saves[i], &s->saves[i + j]))
			{
				ft_printf("FOUND SKIP OF %d\n", j);
			}
			++j;
		}
		*/
	}
}
