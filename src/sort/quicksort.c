#include "sort.h"

static inline void	swap(int *a, int *b)
{
    int temp;

	temp = *a;
    *a = *b;
    *b = temp;
}

/* Quicksort partition function */
static inline int	qsort_partition(int *arr, int *indices, int low, int high)
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
void	quicksort(int *arr, int *indices, int low, int high)
{
	int	pivot;

	if (low < high) {
		pivot = qsort_partition(arr, indices, low, high);
		quicksort(arr, indices, low, pivot - 1);
		quicksort(arr, indices, pivot + 1, high);
	}
}
