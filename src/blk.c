/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"


int	blk_at(struct s_data *data, struct s_blk *blk, size_t i)
{
	size_t					k;
	const struct s_stack	*s = (void *)((blk->dest <= BLK_A_TOP)
			* (unsigned long int)&data->sa + (blk->dest > BLK_A_TOP)
			* (unsigned long int)&data->sb);
	
	k = ((blk->dest & __BLK_POS) == __BLK_TOP) * (s->size - 1 * (!!s->size));
	while (((blk->dest & __BLK_POS) == __BLK_TOP) && --i > 0)
		k = (s->size && k != s->size) * (k + 1) + (!s->size) * k;
	while (((blk->dest & __BLK_POS) == __BLK_BOT) && --i > 0)
		k = (s->size && k != s->size) * (k + 1) + (!s->size) * k;
	return (s->data[i]);
}
