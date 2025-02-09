#ifndef BLK_H
# define BLK_H

# include <stdlib.h>

typedef struct s_state	t_state;

/**
 * @brief Destination for blocks
 */
typedef enum e_blk_dest
{
	//
	__BLK_SEL = 0b10,
	__BLK_A = 0b00,
	__BLK_B = 0b10,
	//
	__BLK_POS = 0b01,
	__BLK_TOP = 0b00,
	__BLK_BOT = 0b01,
	//
	BLK_A_TOP = __BLK_A | __BLK_TOP,
	BLK_A_BOT = __BLK_A | __BLK_BOT,
	BLK_B_TOP = __BLK_B | __BLK_TOP,
	BLK_B_BOT = __BLK_B | __BLK_BOT,
} t_blk_dest;

/**
 * @brief Block
 */
typedef struct s_blk
{
	size_t			size;
	enum e_blk_dest	dest;
}	t_blk;

/**
 * @brief Split of three blocks created from single block
 */
typedef union u_split
{
	struct s_a1
	{
		struct s_blk	_0;
		struct s_blk	_1;
		struct s_blk	_2;
	}	splits;
	struct s_blk	data[3];
}	t_split;

/**
 * @brief Splits original block to 3 smaller blocks
 */
t_split	blk_split(t_state *state, t_blk blk);

/**
 * @brief Moves value from a destination to another destination
 *
 * Moves element at dest `from` to dest `to`.
 *
 * @note In case the move is not possible, nothing happens
 *
 * @param data Program data
 * @param from From destination
 * @param to To destination
 *
 * Move table:
 * From\To |  TOP A  |  TOP B  |  BOT A  |  BOT B  |
 * | TOP A |    x    |   pb    |    ra   | pb   rb |
 * | TOP B | pa      |    x    | pa   ra |   rb    |
 * | BOT A |  ra     | rra  pb |    x    |rra pb rb|
 * | BOT B | rrb  pa |  rb     |rrb pa ra|    x    |
 */
void	blk_move(t_state *state, enum e_blk_dest from, enum e_blk_dest to);

#endif // BLK_H
