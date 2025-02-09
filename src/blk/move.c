#include "blk.h"
#include "../stack/stack.h"
#include "../util.h"
#include <stdint.h>

void	move_blk(t_state *s, enum e_blk_dest from, enum e_blk_dest to)
{
	const uint8_t	id = (from << 2) | to;

	if (((from & __BLK_SEL) == __BLK_A && !s->sa.size)
		|| ((from & __BLK_SEL) == __BLK_B && !s->sb.size))
		return ;
	(void)((!(id % 5))
		|| (id == 1 && (op(s, STACK_OP_PB), 1))
		|| (id == 2 && (op(s, STACK_OP_RA), 1))
		|| (id == 3 && (op(s, STACK_OP_PB), op(s, STACK_OP_RB), 1))
		|| (id == 4 && (op(s, STACK_OP_PA), 1))
		|| (id == 6 && (op(s, STACK_OP_PA), op(s, STACK_OP_RA), 1))
		|| (id == 7 && (op(s, STACK_OP_RB), 1))
		|| (id == 8 && (op(s, STACK_OP_RA), 1))
		|| (id == 9 && (op(s, STACK_OP_RRA), op(s, STACK_OP_PB), 1))
		|| (id == 11 && (op(s, STACK_OP_RRA), op(s, STACK_OP_PB),
				op(s, STACK_OP_RB), 1))
		|| (id == 12 && (op(s, STACK_OP_RRB), op(s, STACK_OP_PA), 1))
		|| (id == 13 && (op(s, STACK_OP_RB), 1))
		|| (id == 14 && (op(s, STACK_OP_RRB), op(s, STACK_OP_PA),
				op(s, STACK_OP_RA), 1)));
}
