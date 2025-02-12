#include "state.h"
#include <stdint.h>
#include <stdlib.h>
#include <ft_printf.h>

t_state	state_new(const t_pivots_cfg *pivots, uint32_t seed, size_t sz)
{
	int	*buf;

	buf = malloc(sz * sizeof(int));
	if (!buf)
	{
		ft_dprintf(2, "%s: malloc() failed\n", __FUNCTION__);
		exit(1);
	}
	return ((t_state){
		.sa = stack_new(sz),
		.sb = stack_new(sz),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
		.saves = NULL,
		.saves_size = 0,
		.saves_cap = 0,
		.tmp_buffer = buf,
		.seed = seed,
		.annealing_depth = 0,
		.pivots = pivots,
	});
}

void	state_free(t_state *state)
{
	while (state->saves_size--)
	{
		stack_free(&state->saves[state->saves_size].sa);
		stack_free(&state->saves[state->saves_size].sb);
	}
	stack_free(&state->sa);
	stack_free(&state->sb);
	free(state->ops);
	free(state->saves);
	free(state->tmp_buffer);
}

void	state_dump(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < state->op_size)
		ft_printf("%s\n", stack_op_name(state->ops[i++]));
	state->op_size = 0;
}
