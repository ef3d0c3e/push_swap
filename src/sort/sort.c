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
#include <ft_printf.h>
#include "sort.h"
#include "../stack/stack.h"
#include "../blk/blk.h"
#include "../state/state.h"

/* Replaces values with their index, e.g the smallest value becomes 0, the next
 * smallest 1, etc.. */
static void	replace_with_index(struct s_stack *sa)
{
	int		*indices;
	size_t	i;

	indices = malloc(sizeof(int) * sa->size);
	i = 0;
	while (i++ < sa->size)
		indices[i - 1] = i - 1;
	quicksort_indices(sa->data, indices, 0, sa->size - 1);
	i = 0;
	while (i++ < sa->size)
		sa->data[indices[i - 1]] = i - 1;
	free(indices);
}

void	sort_stack(t_state *s)
{
	t_blk	blk;

	replace_with_index(&s->sa);
	state_create_savestate(s);
	if (stack_sorted(&s->sa) || s->sa.size < 2)
		return ;
	blk = (t_blk){.dest = BLK_A_TOP, .size = s->sa.size};
	blk_sort(s, &blk);
}
