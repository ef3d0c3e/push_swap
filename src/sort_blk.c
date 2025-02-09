/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_blk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void move_to(struct s_data *data, enum e_blk_dest dest)
{
	if (dest == BLK_B_BOT)
	{
		op(data, STACK_OP_PB);
		op(data, STACK_OP_RB);
	}
	else if (dest == BLK_B_TOP)
	{
		op(data, STACK_OP_PB);
	}
	else if (dest == BLK_A_BOT)
	{
		op(data, STACK_OP_RA);
	}
}

static void from_to(struct s_data *data, enum e_blk_dest from, enum e_blk_dest to)
{
}

static union u_split blk_split(struct s_data *data, struct s_blk *blk)
{
	struct s_stack	*stack = (struct s_stack*[2])
			{&data->sa, &data->sb}[blk->dest & __BLK_B];
	const union u_split split = { .splits = {
		._0 = (struct s_blk){
			.size = blk->size / 3,
			.dest = BLK_B_BOT,
		},
		._1 = (struct s_blk){
			.size = blk->size / 3,
			.dest = BLK_B_TOP,
		},
		._2 = (struct s_blk){
			.size = blk->size - 2 * (blk->size / 3),
			.dest = BLK_A_BOT,
		}
	}};
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < split.data[i].size)
		{
			move_to(data, split.data[i].dest);
			++j;
		}
		++i;
	}

		
	return (split);
}

static void rec_sort_blk(struct s_data *data, struct s_blk *blk)
{
	if (blk->size == 2)
		return (sort_2(data, blk));

	blk_split(data, blk);
}


void	blk_sort(struct s_data *data)
{
	struct s_blk	blk;

	blk.dest = BLK_A_TOP;
	blk.size = data->sa.size;
	rec_sort_blk(data, &blk);
}
