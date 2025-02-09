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

# include "stack/stack.h"

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
 * @brief Output and clears the data's ops array
 *
 * @param data Data to display
 */
void			data_dump(struct s_data *data);

/**
 * @brief Memcpy implementation from libft
 */
void			*ft_memcpy(void *dest, const void *src, size_t n);

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

void			blk_sort(struct s_data *data);

void			sort_stack(struct s_data *data);

#endif // PUSH_SWAP_H
