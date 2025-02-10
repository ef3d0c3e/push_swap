#include "../state.h"
#include "ft_printf.h"

int	compare_states(t_savestate *sim, t_savestate *orig)
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

void	opti(const t_state *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < s->op_size)
	{
		//new = state_savestate(&s->saves[i]);
		
		j = 1;
		while (j < 10 && i + j < s->saves_size)
		{
			if (compare_states(&s->saves[i], &s->saves[i + j]))
			{
				ft_printf("FOUND SKIP OF %d\n", j);
			}
			++j;
		}
		++i;
	}
;
	i = 0;
	while (i < s->op_size)
	{
		stack_free(&s->saves[i].sa);
		stack_free(&s->saves[i].sb);++i;
		++i;
	}
}
