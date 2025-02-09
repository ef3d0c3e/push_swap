#ifndef BLK_H
#define BLK_H

#include <stdlib.h>

enum	e_blk_dest
{
	__BLK_SEL = 0b10,
	__BLK_A = 0b00,
	__BLK_B = 0b10,

	__BLK_POS = 0b01,
	__BLK_BOT = 0b00,
	__BLK_TOP = 0b01,

	BLK_A_BOT = __BLK_A | __BLK_BOT,
	BLK_A_TOP = __BLK_A | __BLK_TOP,
	BLK_B_BOT = __BLK_B | __BLK_BOT,
	BLK_B_TOP = __BLK_B | __BLK_TOP,
};

struct	s_blk
{
	enum e_blk_dest	dest;
	size_t			size;
};

union u_split
{
	struct
	{
		struct s_blk	_0;
		struct s_blk	_1;
		struct s_blk	_2;
	} splits;
	struct s_blk	data[3];
};

void	move_fromto(struct s_data *data, enum e_blk_dest from, enum e_blk_dest to);

void			sort_2(struct s_data *data, struct s_blk *blk);

#endif // BLK_H
