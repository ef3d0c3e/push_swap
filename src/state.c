#include "state.h"
#include "blk/blk.h"
#include <ft_printf.h>

t_state	state_new(size_t sz)
{
	return ((t_state){
		.sa = stack_new(sz),
		.sb = stack_new(sz),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
	});
}

void	state_free(t_state *state)
{
	stack_free(&state->sa);
	stack_free(&state->sb);
	free(state->ops);
}

void	state_dump(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < state->op_size)
		ft_printf("%s\n", stack_op_name(state->ops[i++]));
	state->op_size = 0;
}

void	state_pivots(t_state *state, const t_blk *blk, int *p1, int *p2)
{
	// TODO: Heuristics
	*p1 = blk->size / 3;
	*p2 = *p1 + *p1;
	*p2 = blk_value(state, blk, *p1);
	*p1 = blk_value(state, blk, *p2);
}
