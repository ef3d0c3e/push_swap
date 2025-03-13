/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blk.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BLK_H
# define BLK_H

# include <stdlib.h>

typedef struct s_state	t_state;
typedef struct s_stack	t_stack;

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
	BLK_A_TOP = __BLK_A | __BLK_TOP, // 00
	BLK_A_BOT = __BLK_A | __BLK_BOT, // 01
	BLK_B_TOP = __BLK_B | __BLK_TOP, // 10
	BLK_B_BOT = __BLK_B | __BLK_BOT, // 11
}	t_blk_dest;

/**
 * @brief Gets the name of a destination
 *
 * This is mostly used for debugging
 *
 * @param dest Destination to get the name of
 */
const char
*blk_dest_name(enum e_blk_dest dest);

/**
 * @brief Block
 */
typedef struct s_blk
{
	size_t			size;
	enum e_blk_dest	dest;
}	t_blk;

/**
 * @brief Gets the value at a given position
 */
int
blk_value(const t_state *s, const t_blk *blk, size_t pos);

/**
 * @brief Gets the stack from a destination
 *
 * @param s State
 * @param dest Destination to get the stack for
 *
 * @returns The stack for dest
 */
const t_stack
*blk_stack(const t_state *s, enum e_blk_dest dest);

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
t_split
blk_split(t_state *state, t_blk *blk, int p1, int p2);

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
 * From\To |  TOP A  |  BOT A  | TOP B  |  BOT B  |
 * | TOP A |    x    |    ra   |  pb    | pb   rb |
 * | BOT A |  rra    |    x    |rra  pb |rra pb rb|
 * | TOP B | pa      | pa   ra |   x    |   rb    |
 * | BOT B | rrb  pa |rrb pa ra| rrb    |    x    |
 */
void
blk_move(t_state *state, enum e_blk_dest from, enum e_blk_dest to);

/**
 * @brief Sorts two elements
 *
 * @param state The state
 * @param blk The block to sort
 */
void
blk_sort_2(t_state *state, t_blk *blk);

/**
 * @brief Sorts three elements
 *
 * @param state The state
 * @param blk The block to sort
 */
void	blk_sort_3(t_state *state, t_blk *blk);

/**
 * @brief Sorts a small number elements on the block (for N <= 3 elements)
 *
 * @param state The state
 * @param blk The block to sort
 */
void	blk_sort_small(t_state *state, t_blk *blk);

/**
 * @brief Sort a block by recursively splitting it and calling `blk_sort_small`
 *
 * @param state The state
 * @param blk The block to sort
 */
void	blk_sort(t_state *state, t_blk *blk);

/**
 * @brief Checks if a block is absolutely sorted
 *
 * @param s The state
 * @param dest The destination
 * @param offset Start offset of the check
 */
int		blk_abs_sorted(const t_state *s, enum e_blk_dest dest, size_t offset);

#endif // BLK_H
