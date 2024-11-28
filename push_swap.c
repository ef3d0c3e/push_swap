#include "libs/ft_printf/src/ft_printf.h"
#include "libs/ft_printf/src/ft_printf_bonus.h"
#include "stack.h"
#include <limits.h>
#include <stddef.h>

#define _stack_op(sa, sb, op ) \
{ \
	ft_printf("%s\n", stack_op_name(op)); \
	stack_op(sa, sb, op); \
}

#include <stdlib.h>
#include <stdbool.h>

// Utility function to check if stack is sorted
bool is_stack_sorted(struct s_stack *sa) {
    if (sa->size <= 1)
        return true;
    
    for (size_t i = 1; i < sa->size; i++) {
        if (sa->data[i-1] > sa->data[i])
            return false;
    }
    return true;
}

// Utility function to find median of stack elements
int find_median(struct s_stack *sa) {
    // Create a copy of the stack data to avoid modifying original
    int *sorted_copy = malloc(sa->size * sizeof(int));
    if (!sorted_copy) return 0;  // Error handling

    // Copy data
    for (size_t i = 0; i < sa->size; i++) {
        sorted_copy[i] = sa->data[i];
    }

    // Sort the copy
    for (size_t i = 0; i < sa->size - 1; i++) {
        for (size_t j = 0; j < sa->size - i - 1; j++) {
            if (sorted_copy[j] > sorted_copy[j + 1]) {
                int temp = sorted_copy[j];
                sorted_copy[j] = sorted_copy[j + 1];
                sorted_copy[j + 1] = temp;
            }
        }
    }

    // Find median
    int median = sorted_copy[sa->size / 2];
    
    free(sorted_copy);
    return median;
}

void sort_small_stack(struct s_stack *sa, struct s_stack *sb) {
    if (sa->size == 2) {
        // If first > second, swap
        if (sa->data[0] > sa->data[1]) {
            _stack_op(sa, sb, STACK_OP_SA);
        }
        return;
    }

    if (sa->size == 3) {
        // Comprehensive cases for 3-element sorting
        if (sa->data[0] > sa->data[1] && sa->data[0] > sa->data[2]) {
            // Largest element is at top
            _stack_op(sa, sb, STACK_OP_RA);
        }
        
        if (sa->data[0] > sa->data[1]) {
            _stack_op(sa, sb, STACK_OP_SA);
        }
        
        if (sa->data[1] > sa->data[2]) {
            _stack_op(sa, sb, STACK_OP_RRA);
            _stack_op(sa, sb, STACK_OP_SA);
        }
    }
}

// Main sorting algorithm
void generalized_stack_sort(struct s_stack *sa, struct s_stack *sb) {
    // Handle trivial cases
    if (sa->size <= 1 || is_stack_sorted(sa)) 
        return;

    // Special handling for small stacks
    if (sa->size <= 3) {
        sort_small_stack(sa, sb);
        return;
    }

    // Find the median to use as a pivot
    int median = find_median(sa);

    // Partition the stack using the median
    size_t original_size = sa->size;
    size_t pushed_to_b = 0;

    // First pass: push elements <= median to B
    for (size_t i = 0; i < original_size; i++) {
        if (sa->data[0] <= median) {
            _stack_op(sa, sb, STACK_OP_PB);
            pushed_to_b++;
        } else {
            _stack_op(sa, sb, STACK_OP_RA);
        }
    }

    // Recursive sorting of two partitions
    // Sort the remaining elements in A
    generalized_stack_sort(sa, sb);

    // Push back elements from B to A
    while (pushed_to_b > 0) {
        _stack_op(sa, sb, STACK_OP_PA);
        pushed_to_b--;
    }
}

// Wrapper function to call the sorting algorithm
void stack_sort(struct s_stack *sa, struct s_stack *sb) {
    // Ensure B is empty before starting
    while (sb->size > 0) {
        _stack_op(sa, sb, STACK_OP_PA);
    }

    // Call the generalized sorting algorithm
    generalized_stack_sort(sa, sb);
}

int main(int ac, char **av)
{
	struct s_stack	sa;
	struct s_stack	sb;
	size_t			i;

	if (ac < 2)
	{
		ft_dprintf(2, "Usage: %s NUMBERS...\n", av[0]);
		exit(1);
	}
	sa = stack_new(ac - 1);
	sb = stack_new(ac - 1);
	i = 1;
	while (i < ac)
		sa.data[sa.size++] = atoi(av[i++]);

	stack_sort(&sa, &sb);
	i = 0;
	ft_printf("---\n");
	while (i < sa.size)
	{
		ft_printf("%d ", sa.data[i]);
		++i;
	}

	return 0;
}
