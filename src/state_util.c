#include "state.h"
#include "util.h"
#include <ft_printf.h>

t_state			state_partial_clone(const t_state *state)
{
	return ((t_state){
		.sa = stack_clone(&state->sa),
		.sb = stack_clone(&state->sb),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
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

t_savestate	*state_create_savestate(t_state *s)
{
	t_savestate	*new;

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
	return (&s->saves[s->saves_size++]);
}
