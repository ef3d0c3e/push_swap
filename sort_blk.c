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

static void	top(struct s_data *data, struct s_blk *blk)
{
	if (blk->dest == BLK_B_BOT && data->sb.size == blk->size)
		blk->dest = BLK_B_TOP;
	if (blk->dest == BLK_A_BOT && data->sb.size == blk->size)
		blk->dest = BLK_A_TOP;
}

void	sort_blk(struct s_data *data, struct s_blk blk)
{
	struct s_blk_split	split;

	top(data, &blk);
}
