/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ARGS_H
# define ARGS_H

# include "state/state.h"

/**
 * @brief Parses arguments and create state from arguments
 *
 * @note Will `exit(1)` on failure.
 *
 * @param pivots The pivots data, NULL if unused
 * @param argc Number of arguments (numbers on the stack)
 * @param argv Arguments (unique positive integer to add to the stack)
 *
 * @returns The parsed initial state
 */
t_state	parse_args(const t_pivots_cfg *pivots, int argc, char **argv);

#endif // ARGS_H
