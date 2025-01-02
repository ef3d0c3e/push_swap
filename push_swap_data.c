/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

struct s_data	data_new(size_t sz)
{
	return ((struct s_data){
		.sa = stack_new(sz),
		.sb = stack_new(sz),
		.ops = NULL,
		.op_size = 0,
		.op_cap = 0,
	});
}

void	data_free(struct s_data *data)
{
	stack_free(&data->sa);
	stack_free(&data->sb);
	free(data->ops);
}
