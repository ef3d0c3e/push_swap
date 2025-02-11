#include "state.h"
#include "../util.h"
#include <ft_printf.h>

t_state			state_partial_clone(const t_state *s)
{
	int	*buf;

	buf = malloc(s->sa.capacity * sizeof(int));
	if (!buf)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}
	return ((t_state){
		.sa = stack_clone(&s->sa),
		.sb = stack_clone(&s->sb),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = (size_t)-1,
		.tmp_buffer = buf,
		.seed = s->seed,
		.pivots = s->pivots,
	});
}

t_state	state_from_savestate(const t_savestate	*save)
{
	/*
	enum e_stack_op	*ops;

	ops = malloc(save->id * sizeof(enum e_stack_op));
	if (!ops)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}*/
	return ((t_state){
		.sa = stack_clone(&save->sa),
		.sb = stack_clone(&save->sb),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
	});
}

void	state_create_savestate(t_state *s)
{
	t_savestate	*new;

	if (s->saves_cap == (size_t)-1)
		return ;
	if (!s->saves || s->saves_cap == s->saves_size)
	{
		new = malloc(sizeof(t_savestate) * ((s->saves_cap + !s->saves_cap) << 1));
		if (!new)
		{
			ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
			exit(1);
		}
		ft_memcpy(new, s->saves, sizeof(t_savestate) * s->saves_size);
		free(s->saves);
		s->saves = new;
		s->saves_cap = (s->saves_cap + !s->saves_cap) << 1;
	}
	s->saves[s->saves_size] = (t_savestate){
		.sa = stack_clone(&s->sa),
		.sb = stack_clone(&s->sb),
		.ops = s->ops,
		.id = s->saves_size,
	};
	++s->saves_size;
}

void	op(t_state *state, enum e_stack_op op)
{
	enum e_stack_op	*tmp;
	size_t			i;

	if (!state->saves)
		state_create_savestate(state);
	if (!stack_op_useful(state, op))
		return;
	if (state->op_size >= state->op_cap)
	{
		tmp = malloc(sizeof(op) * ((state->op_cap + !state->op_cap) << 1));
		if (!tmp)
		{
			ft_dprintf(2, "Error\n");
			exit(1);
		}
		i = 0;
		while (i++ < state->op_size)
			tmp[i - 1] = state->ops[i - 1];
		free(state->ops);
		state->ops = tmp;
		state->op_cap = (state->op_cap + !state->op_cap) << 1;
	}
	state->ops[state->op_size++] = op;
	stack_op(&state->sa, &state->sb, op);
	state_create_savestate(state);

	// debug
	if (0)
	{
		ft_printf("%s\nA: ", stack_op_name(op));
		i = 0;
		while (i < state->sa.size)
		{
			ft_printf("%d ", state->sa.data[i]);
			++i;
		}

		ft_printf("\nB: ");
		i = 0;
		while (i < state->sb.size)
		{
			ft_printf("%d ", state->sb.data[i]);
			++i;
		}
		ft_printf("\n-----\n");
	}
}
