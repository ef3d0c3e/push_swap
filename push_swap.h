/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack.h"

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

struct s_blk_split
{
	struct s_blk	_0;
	struct s_blk	_1;
	struct s_blk	_2;
};

/**
 * @brief Stores data for the push swap operations
 */
struct s_data
{
	struct s_stack	sa;
	struct s_stack	sb;
	/**
	 * @brief Array of used operations
	 *
	 * This is then used for printing
	 */
	enum e_stack_op	*ops;
	/**
	 * @brief Size of the `ops` array
	 */
	size_t			op_size;
	/**
	 * @brief Capacity of the `ops` array
	 */
	size_t			op_cap;
};

/**
 * @brief Creates a new `s_data` structure
 *
 * @param sz The size of the stacks in the s_data structure
 */
struct s_data	data_new(size_t sz);

/**
 * @brief Frees a `s_data` structure
 *
 * @param data Data to free
 */
void			data_free(struct s_data *data);

/**
 * @brief Performs operation `op` on `sa` and `sb` and store the result in data
 *
 * @param data The @ref s_data struct
 * @param op Operation to perform
 */
void			op(struct s_data *data, enum e_stack_op op);

/**
 * @brief Determies whether a stack is sorted
 *
 * @param s Stack to check for sorted
 *
 * @returns 1 If `s` is sorted, 0 otherwise
 */
int				sorted(const struct s_stack *s);

/**
 * @brief Sort a stack (@p sa) of 2 elements
 *
 * Sorting 2 elements is guaranteed to require at most 1 operation.
 *
 * @param sa Stack A
 * @param sb Stack B
 */
void			sort_2(struct s_data *data);

/**
 * @brief Sort a stack (@p sa) of 3 elements
 *
 * Sorting 3 elements is guaranteed to require at most 2 operations.
 *
 * @param sa Stack A
 * @param sb Stack B
 */
void			sort_3(struct s_data *data);
/**
 * @brief Sort a stack (@p sa) of 5 elements
 *
 * @param sa Stack A
 * @param sb Stack B
 */
void			sort_5(struct s_data *data);

void			sort_blk(struct s_data *data, struct s_blk blk);

void			sort_stack(struct s_data *data);

#endif // PUSH_SWAP_H
