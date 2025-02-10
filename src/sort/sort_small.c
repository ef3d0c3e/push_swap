/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "push_swap.h"

/*
void	sort_2(struct s_data *data)
{
	if (data->sa.data[0] > data->sa.data[1])
		op(data, STACK_OP_SA);
}

void	sort_3(struct s_data *data)
{
	const int	top = data->sa.data[data->sa.size - 3];
	const int	mid = data->sa.data[data->sa.size - 2];
	const int	bot = data->sa.data[data->sa.size - 1];

	if (top > mid && bot > mid && bot > top)
		op(data, STACK_OP_SA);
	else if (top > mid && bot > mid && top > bot)
		op(data, STACK_OP_RA);
	else if (mid > top && mid > bot && top > bot)
		op(data, STACK_OP_RRA);
	else if (mid > top && mid > bot && bot > top)
	{
		op(data, STACK_OP_SA);
		op(data, STACK_OP_RA);
	}
	else if (top > mid && mid > bot && top > bot)
	{
		op(data, STACK_OP_SA);
		op(data, STACK_OP_RRA);
	}
}

void	sort_4(struct s_data *data)
{
	int	rank;

	while (data->sa.size > 3)
	{
		rank = (data->sa.data[0] < data->sa.data[1]) + (data->sa.data[0] < data->sa.data[2]) + (data->sa.data[0] < data->sa.data[3]);
		if (rank >= 3)
			op(data, STACK_OP_PB);
		else
			op(data, STACK_OP_RA);
		if (sorted(&data->sa) && !data->sb.size)
			return;
	}
	sort_3(data);
	op(data, STACK_OP_PA);
	if (data->sa.data[0] > data->sa.data[1])
		op(data, STACK_OP_SA);
}

void	sort_5(struct s_data *data)
{
	int	rank;

	while (data->sa.size > 3)
	{
		rank = (data->sa.data[0] < data->sa.data[1]) + (data->sa.data[0] < data->sa.data[2]) + (data->sa.data[0] < data->sa.data[3]);
		if (rank >= 3)
			op(data, STACK_OP_PB);
		else
			op(data, STACK_OP_RA);
		if (sorted(&data->sa) && !data->sb.size)
			return;
	}
	if (data->sb.data[0] < data->sb.data[1])
		op(data, STACK_OP_SB);
	sort_3(data);
	op(data, STACK_OP_PA);
	op(data, STACK_OP_PA);
}
*/
