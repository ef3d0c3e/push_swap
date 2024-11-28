#include "libs/ft_printf/src/ft_printf.h"
#include "stack.h"
#include "libs/ft_printf/src/ft_printf_bonus.h"
#include <limits.h>

void			_stack_op(struct s_stack *sa,
		struct s_stack *sb,
		enum stack_op op)
{
	ft_printf("%d: %s\n", op, stack_op_name(op));
	stack_op(sa, sb, op);
}

void sort_stack(struct s_stack *sa, struct s_stack *sb) {
	while (sa->size > 0) {
		int min = INT_MAX;
		int min_index = -1;

		// Find the minimum element in stack A
		for (size_t i = 0; i < sa->size; ++i) {
			int top = sa->data[sa->size - 1];
			if (top < min) {
				min = top;
				min_index = i;
			}
			_stack_op(sa, sb, STACK_OP_RA); // Rotate A to inspect the next element
		}

		// Bring the minimum element to the top of stack A
		for (size_t i = 0; i < sa->size - min_index; ++i) {
			_stack_op(sa, sb, STACK_OP_RRA); // Reverse rotate A to position the minimum at the top
		}

		// Push the minimum element to stack B
		_stack_op(sa, sb, STACK_OP_PB);

		// Restore stack A's original order
		for (size_t i = 0; i < min_index; ++i) {
			_stack_op(sa, sb, STACK_OP_RA);
		}
	}

	// Move sorted elements back from stack B to stack A
	while (sb->size > 0) {
		_stack_op(sa, sb, STACK_OP_PA);
	}
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

	sort_stack(&sa, &sb);
	return 0;
}
