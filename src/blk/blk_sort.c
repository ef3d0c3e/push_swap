#include "blk.h"
#include "../util.h"
#include "ft_printf.h"
#include <stdio.h>

void	blk_sort_2(t_state *state, t_blk *blk)
{
	const int	u = blk_value(state, blk, 0);
	const int	v = blk_value(state, blk, 1);

	if (blk->dest == BLK_A_TOP)
		(void)(u > v && (op(state, STACK_OP_SA), 1));
	else if (blk->dest == BLK_A_BOT)
	{
		(void)(op(state, STACK_OP_RRA), op(state, STACK_OP_RRA));
		(void)(u < v && (op(state, STACK_OP_SA), 1));
	}
	else if (blk->dest == BLK_B_TOP)
	{
		(void)(u < v && (op(state, STACK_OP_SB), 1));
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
	}
	else
	{
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_RRB);
		op(state, STACK_OP_PA);
		op(state, STACK_OP_PA);
		(void)(u > v && (op(state, STACK_OP_SA), 1));
	}
	blk->size -= 2;
}

void	blk_sort_small(t_state *state, t_blk *blk)
{
	if (blk->size == 1)
	{
		blk_move(state, blk->dest, BLK_A_TOP);
		blk->size -= 1;
	}
	else if (blk->size == 2)
		blk_sort_2(state, blk);
	else if (blk->size == 3)
		blk_sort_3(state, blk);
}

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

typedef struct s_cost
{
	int	index_b;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_cost;

int	calculate_rotation_cost(int size, int position)
{
	if (position <= size / 2)
		return (position);
	return (-(size - position));
}

static int	find_position_in_a(t_state *s, int index_b)
{
	int	pos;
	int	first_index;
	int	last_index;
	int	current_index;
	int	next_index;

	pos = 0;
	if (!s->sa.size)
		return (0);
	first_index = s->sa.data[0];
	last_index = s->sa.data[s->sa.size - 1];
	if (index_b < first_index && index_b > last_index)
		return (0);

	size_t i = 0;
	while (i + 1 < s->sa.size)
	{
		current_index = s->sa.data[i];
		next_index = s->sa.data[i + 1];
		if (index_b > current_index && index_b < next_index)
			break ;

		++i;
		pos++;
	}
	return (pos + 1);
}

static int	count_cost(int a, int b)
{
	if (a >= 0 && b >= 0)
	{
		if (a > b)
			return (a);
		return (b);
	}
	if (a < 0 && b < 0)
	{
		if (a < b)
			return (-a);
		return (-b);
	}
	if (a < 0)
		return (-a + b);
	return (-b + a);
}

static t_cost	calculate_best_move(t_state *s)
{
	t_cost	best_move;
	t_cost	tmp_move;
	int		pos[2];
	int		size_a;
	int		size_b;

	best_move.total_cost = 5000;
	pos[0] = 0;
	pos[1] = 0;
	size_a = s->sa.size;
	size_b = s->sb.size;
	size_t	i = 0;
	while (i < s->sb.size)
	{
		tmp_move.index_b = s->sb.data[i];
		tmp_move.cost_b = calculate_rotation_cost(s->sb.size, pos[1]);
		pos[0] = find_position_in_a(s, tmp_move.index_b);
		tmp_move.cost_a = calculate_rotation_cost(size_a, pos[0]);
		tmp_move.total_cost = count_cost(tmp_move.cost_a, tmp_move.cost_b);
		if (tmp_move.total_cost < best_move.total_cost)
			best_move = tmp_move;
		++i;
		pos[1]++;
	}
	return (best_move);
}

static void	execute_simple_rotations(t_state *s, t_cost best_move)
{
	while (best_move.cost_b > 0)
	{
		op(s, STACK_OP_RB);
		best_move.cost_b--;
	}
	while (best_move.cost_b < 0)
	{
		op(s, STACK_OP_RRB);
		best_move.cost_b++;
	}
	while (best_move.cost_a > 0)
	{
		op(s, STACK_OP_RA);
		best_move.cost_a--;
	}
	while (best_move.cost_a < 0)
	{
		op(s, STACK_OP_RRA);
		best_move.cost_a++;
	}
}

static void	execute_double_rotations(t_state *s, t_cost best_move)
{
	while (best_move.cost_a > 0 && best_move.cost_b > 0)
	{
		op(s, STACK_OP_RR);
		best_move.cost_a--;
		best_move.cost_b--;
	}
	while (best_move.cost_a < 0 && best_move.cost_b < 0)
	{
		op(s, STACK_OP_RRR);
		best_move.cost_a++;
		best_move.cost_b++;
	}
	execute_simple_rotations(s, best_move);
}

static int	get_min_position(t_stack *s)
{
	size_t	i;
	int	index_a;

	i = 0;
	while (i < s->size)
	{
		index_a = s->data[i];
		if (index_a == 0)
			break ;
		i++;
	}
	return (i);
}

void	end_sort(t_state *s)
{
	int	cost;

	ps("end_sort", s);
	cost = calculate_rotation_cost(s->sa.size, get_min_position(&s->sa));
	while (cost > 0)
	{
		op(s, STACK_OP_RA);
		cost--;
	}
	while (cost < 0)
	{
		op(s, STACK_OP_RRA);
		cost++;
	}
}

static void	pre_sort_rr(t_state *s, int *limits)
{
	int	index_a_next;

	op(s, STACK_OP_PB);
	index_a_next = s->sa.data[0];
	ft_printf("ind=%d\n", index_a_next);
	if (!(index_a_next >= limits[1] && index_a_next < limits[2])
		&& !(index_a_next < limits[1] && index_a_next >= limits[0]))
		op(s, STACK_OP_RR);
	else
		op(s, STACK_OP_RB);
}

void pre(t_state *s)
{
	int	i;
	int	index_a;
	int limits[3];

	limits[0] = 1;
	limits[1] = s->sa.capacity / 2;
	limits[2] = s->sa.capacity - 1;

	i = s->sb.size;
	while (i < (limits[2] - limits[0]) && s->sa.size)
	{
		index_a = s->sa.data[0];
		if (index_a >= limits[1] && index_a < limits[2])
		{
			op(s, STACK_OP_PB);
			i++;
		}
		else if (index_a < limits[1] && index_a >= limits[0])
		{
			pre_sort_rr(s, limits);
			i++;
		}
		else
			op(s, STACK_OP_RA);
	}
}

void	blk_sort(t_state *s, t_blk *blk)
{
	ps("BEF Split", s);
	
	pre(s);
	while (s->sb.size)
	{
		t_cost best_move = calculate_best_move(s);
		execute_double_rotations(s, best_move);
		op(s, STACK_OP_PA);
	}
	end_sort(s);
	ps("After", s);

	/*
	t_split	split;
	size_t	i;
	int	pivots[2];

	if (blk->dest == BLK_A_BOT && s->sa.size == blk->size)
		blk->dest = BLK_A_TOP;
	else if (blk->dest == BLK_B_BOT && s->sb.size == blk->size)
		blk->dest = BLK_B_TOP;
	if (blk->size <= 3)
	{
		(blk_sort_small(s, blk));
		return ;
	}
	pivots_next(s, blk, pivots, pivots + 1);
	ps("BEF Split", s);
	split = blk_split(s, blk, pivots[0], pivots[1]);
	ps("AFT Split", s);
	i = 0;
	while (i < 3)
	{
		blk_sort(s, &split.data[2 - i]);
		++i;
	}*/
}
