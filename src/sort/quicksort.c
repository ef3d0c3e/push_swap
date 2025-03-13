/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static inline void
	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/* Quicksort partition function */
static inline int
	qsort_partition_indices(int *arr, int *indices, int low, int high)
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
void
	quicksort_indices(int *arr, int *indices, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = qsort_partition_indices(arr, indices, low, high);
		quicksort_indices(arr, indices, low, pivot - 1);
		quicksort_indices(arr, indices, pivot + 1, high);
	}
}

static inline int
	qsort_partition(int *arr, int low, int high)
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
		}
		++j;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void
	quicksort(int *arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = qsort_partition(arr, low, high);
		quicksort(arr, low, pivot - 1);
		quicksort(arr, pivot + 1, high);
	}
}
