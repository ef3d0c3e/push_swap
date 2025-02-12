#include "stack.h"
#include "../state/state.h"

int	stack_op_useful(const t_state *s, enum e_stack_op op)
{
	const enum e_stack_op	operands = op & __STACK_OPERAND;
	const enum e_stack_op	operator = op & __STACK_OPERATOR;
	int						val;

	val = 0;
	if (operands & __STACK_OP_SEL_A)
		val |= ((operator == __STACK_OP_PUSH && s->sb.size != 0)
			|| (operator == __STACK_OP_ROTATE && s->sa.size > 1)
			|| (operator == __STACK_OP_REV_ROTATE && s->sa.size > 1)
			|| (operator == __STACK_OP_SWAP && s->sa.size > 1));
	if (operands & __STACK_OP_SEL_B)
		val |= ((operator == __STACK_OP_PUSH && s->sa.size != 0)
			|| (operator == __STACK_OP_ROTATE && s->sb.size > 1)
			|| (operator == __STACK_OP_REV_ROTATE && s->sb.size > 1)
			|| (operator == __STACK_OP_SWAP && s->sb.size > 1));
	return (val);
}
