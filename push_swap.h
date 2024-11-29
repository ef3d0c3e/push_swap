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
	BLK_A_TOP,
	BLK_A_BOT,
	BLK_B_TOP,
	BLK_B_BOT,
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

struct s_data
{
	struct s_stack	sa;
	struct s_stack	sb;
	enum e_stack_op	*ops;
	size_t			op_size;
	size_t			op_cap;
};

struct s_data	data_new(size_t sz);

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
