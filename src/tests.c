#include <ft_printf.h>
#include "util.h"
#include "sort/sort.h"

static const int	three_permuts[6][3] = {
	{0, 1, 2},
	{0, 2, 1},
	{1, 0, 2},
	{1, 2, 0},
	{2, 0, 1},
	{2, 1, 0},
};

static const int	four_permuts[24][4] = {
	{0,1,2,3},
	{0,1,3,2},
	{0,2,1,3},
	{0,2,3,1},
	{0,3,1,2},
	{0,3,2,1},
	{1,0,2,3},
	{1,0,3,2},
	{1,2,0,3},
	{1,2,3,0},
	{1,3,0,2},
	{1,3,2,0},
	{2,0,1,3},
	{2,0,3,1},
	{2,1,0,3},
	{2,1,3,0},
	{2,3,0,1},
	{2,3,1,0},
	{3,0,1,2},
	{3,0,2,1},
	{3,1,0,2},
	{3,1,2,0},
	{3,2,0,1},
	{3,2,1,0},
};

static const int	five_permuts[120][5] = {
	{0,1,2,3,4},
	{0,1,2,4,3},
	{0,1,3,2,4},
	{0,1,3,4,2},
	{0,1,4,2,3},
	{0,1,4,3,2},
	{0,2,1,3,4},
	{0,2,1,4,3},
	{0,2,3,1,4},
	{0,2,3,4,1},
	{0,2,4,1,3},
	{0,2,4,3,1},
	{0,3,1,2,4},
	{0,3,1,4,2},
	{0,3,2,1,4},
	{0,3,2,4,1},
	{0,3,4,1,2},
	{0,3,4,2,1},
	{0,4,1,2,3},
	{0,4,1,3,2},
	{0,4,2,1,3},
	{0,4,2,3,1},
	{0,4,3,1,2},
	{0,4,3,2,1},
	{1,0,2,3,4},
	{1,0,2,4,3},
	{1,0,3,2,4},
	{1,0,3,4,2},
	{1,0,4,2,3},
	{1,0,4,3,2},
	{1,2,0,3,4},
	{1,2,0,4,3},
	{1,2,3,0,4},
	{1,2,3,4,0},
	{1,2,4,0,3},
	{1,2,4,3,0},
	{1,3,0,2,4},
	{1,3,0,4,2},
	{1,3,2,0,4},
	{1,3,2,4,0},
	{1,3,4,0,2},
	{1,3,4,2,0},
	{1,4,0,2,3},
	{1,4,0,3,2},
	{1,4,2,0,3},
	{1,4,2,3,0},
	{1,4,3,0,2},
	{1,4,3,2,0},
	{2,0,1,3,4},
	{2,0,1,4,3},
	{2,0,3,1,4},
	{2,0,3,4,1},
	{2,0,4,1,3},
	{2,0,4,3,1},
	{2,1,0,3,4},
	{2,1,0,4,3},
	{2,1,3,0,4},
	{2,1,3,4,0},
	{2,1,4,0,3},
	{2,1,4,3,0},
	{2,3,0,1,4},
	{2,3,0,4,1},
	{2,3,1,0,4},
	{2,3,1,4,0},
	{2,3,4,0,1},
	{2,3,4,1,0},
	{2,4,0,1,3},
	{2,4,0,3,1},
	{2,4,1,0,3},
	{2,4,1,3,0},
	{2,4,3,0,1},
	{2,4,3,1,0},
	{3,0,1,2,4},
	{3,0,1,4,2},
	{3,0,2,1,4},
	{3,0,2,4,1},
	{3,0,4,1,2},
	{3,0,4,2,1},
	{3,1,0,2,4},
	{3,1,0,4,2},
	{3,1,2,0,4},
	{3,1,2,4,0},
	{3,1,4,0,2},
	{3,1,4,2,0},
	{3,2,0,1,4},
	{3,2,0,4,1},
	{3,2,1,0,4},
	{3,2,1,4,0},
	{3,2,4,0,1},
	{3,2,4,1,0},
	{3,4,0,1,2},
	{3,4,0,2,1},
	{3,4,1,0,2},
	{3,4,1,2,0},
	{3,4,2,0,1},
	{3,4,2,1,0},
	{4,0,1,2,3},
	{4,0,1,3,2},
	{4,0,2,1,3},
	{4,0,2,3,1},
	{4,0,3,1,2},
	{4,0,3,2,1},
	{4,1,0,2,3},
	{4,1,0,3,2},
	{4,1,2,0,3},
	{4,1,2,3,0},
	{4,1,3,0,2},
	{4,1,3,2,0},
	{4,2,0,1,3},
	{4,2,0,3,1},
	{4,2,1,0,3},
	{4,2,1,3,0},
	{4,2,3,0,1},
	{4,2,3,1,0},
	{4,3,0,1,2},
	{4,3,0,2,1},
	{4,3,1,0,2},
	{4,3,1,2,0},
	{4,3,2,0,1},
	{4,3,2,1,0},
};

void basic_tests()
{
	struct s_state	state;
	size_t			i;
	size_t			j;

	state = state_new(3);
	i = 0;
	while (i < 6)
	{
		state.op_size = 0;
		state.sb.size = 0;
		state.sa.size = 3;
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, three_permuts[i], 3 * sizeof(int));
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
			continue;
		ft_dprintf(2, "Failed to sort permutation of 3.\nInput : ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", three_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 3)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
	}
	state_free(&state);

	i = 0;
	while (i < 24)
	{
		state = state_new(4);
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, four_permuts[i], 4 * sizeof(int));
		j = 0;
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
		{
			state_free(&state);
			continue;
		}
		ft_dprintf(2, "Failed to sort permutation of 4.\nInput : ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", four_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 4)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
		state_free(&state);
	}

	i = 0;
	while (i < 120)
	{
		state = state_new(5);
		state.sa.data = (int*)state.sa.start + state.sa.capacity;
		ft_memcpy(state.sa.data, five_permuts[i], 5 * sizeof(int));
		j = 0;
		sort_stack(&state);
		++i;
		if (stack_sorted(&state.sa))
		{
			state_free(&state);
			continue;
		}
		ft_dprintf(2, "Failed to sort permutation of 5.\nInput : ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", five_permuts[i - 1][j++]);
		ft_dprintf(2, "\nOutput: ");
		j = 0;
		while (j < 5)
			ft_dprintf(2, "%d ", state.sa.data[j++]);
		ft_dprintf(2, "\n");
		state_free(&state);
	}
}
