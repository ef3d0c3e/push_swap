#include "state.h"
#include "blk/blk.h"
#include "stack/stack.h"
#include "util.h"
#include <ft_printf.h>

t_state	state_new(size_t sz)
{
	return ((t_state){
		.sa = stack_new(sz),
		.sb = stack_new(sz),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
	});
}

void	state_free(t_state *state)
{
	stack_free(&state->sa);
	stack_free(&state->sb);
	free(state->ops);
	free(state->saves);
}

void	state_dump(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < state->op_size)
		ft_printf("%s\n", stack_op_name(state->ops[i++]));
	state->op_size = 0;
}

t_state	state_savestate(t_savestate	*save)
{
	enum e_stack_op	*ops;

	ops = malloc(save->id * sizeof(enum e_stack_op));
	if (!ops)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}
	return ((t_state){
		.sa = save->sa,
		.sb = save->sb,
		.ops = ft_memcpy(ops, save->ops, save->id * sizeof(enum e_stack_op)),
		.op_size = save->id,
		.op_cap = save->id,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
	});
}

void	state_pivots(t_state *state, const t_blk *blk, int *p1, int *p2)
{
	return blk_quartiles(state, blk, p1, p2);
}
