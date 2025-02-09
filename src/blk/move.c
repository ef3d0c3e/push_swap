#include "blk.h"

static inline void move_from_a_top(struct s_data *data, enum e_blk_dest to)
{
}

static inline void move_from_a_bot(struct s_data *data, enum e_blk_dest to)
{
}

static inline void move_from_b_top(struct s_data *data, enum e_blk_dest to)
{
}

static inline void move_from_b_bot(struct s_data *data, enum e_blk_dest to)
{
}

void	move_fromto(struct s_data *data, enum e_blk_dest from, enum e_blk_dest to) {
	if (from == BLK_A_TOP)
		move_from_a_top(data, to);
	else if (from == BLK_A_BOT)
		move_from_a_bot(data, to);
}
