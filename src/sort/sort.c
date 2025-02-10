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
#include "../state.h"
#include "../util.h"

static void	swap(int *a, int *b)
{
    int temp;

	temp = *a;
    *a = *b;
    *b = temp;
}

/* Quicksort partition function */
static int	qsort_partition(int *arr, int *indices, int low, int high)
{
    int	pivot;
    int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			++i;
            swap(&arr[i], &arr[j]);
            swap(&indices[i], &indices[j]);
		}
		++j;
	}
    swap(&arr[i + 1], &arr[high]);
    swap(&indices[i + 1], &indices[high]);
    return (i + 1);
}

/* Modified quicksort */
static void	quicksort(int *arr, int *indices, int low, int high)
{
	int	pivot;

	if (low < high) {
		pivot = qsort_partition(arr, indices, low, high);
		quicksort(arr, indices, low, pivot - 1);
		quicksort(arr, indices, pivot + 1, high);
	}
}


/* Replaces values with their index, e.g the smallest value becomes 0, the next smallest 1, etc.. */
static void	replace_with_index(struct s_stack *sa)
{
	int		*indices;
	size_t	i;

	indices = malloc(sizeof(int) * sa->size);
	i = 0;
	while (i++ < sa->size)
		indices[i - 1] = i - 1;
	quicksort(sa->data, indices, 0, sa->size - 1);
	i = 0;
	while (i++ < sa->size)
		sa->data[indices[i - 1]] = i - 1;
	free(indices);
}

void	sort_stack(t_state *s)
{
	replace_with_index(&s->sa);

	if (stack_sorted(&s->sa) || s->sa.size < 2)
		return ;
	//else if (data->sa.size == 2)
	//	sort_2(data);
	//else if (data->sa.size == 3)
	//	sort_3(data);
	//else if (data->sa.size == 4)
	//	sort_4(data);
	//else if (data->sa.size == 5)
	//	sort_5(data);
	//else
		//blk_sort(data);
	//post_sort_optimization(data);
	t_blk blk = (t_blk){.dest = BLK_A_TOP, .size = s->sa.size};
	blk_sort(s, &blk);
}


