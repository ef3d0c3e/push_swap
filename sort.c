/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	sort_stack(struct s_data *data)
{
	if (sorted(&data->sa))
		return ;
	else if (data->sa.size == 2)
		sort_2(data);
	else if (data->sa.size == 3)
		sort_3(data);
	else if (data->sa.size == 5)
		sort_5(data);
	else
		sort_blk(data, (struct s_blk){BLK_A_TOP, data->sa.size});
	//post_sort_optimization(data);
}


