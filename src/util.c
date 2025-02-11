/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "util.h"
#include "state/state.h"
#include "stack/stack.h"

#include <unistd.h>
#include <ft_printf.h>

/* memcopy from my libft */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*end = (unsigned char*)src + n;
	unsigned char		*wd;
	const unsigned char	*ws;

	wd = dest;
	ws = src;
	while (end - ws >= (long int)sizeof(unsigned long int))
	{
		*(unsigned long int *)wd = *(const unsigned long int *)ws;
		wd += sizeof(unsigned long int);
		ws += sizeof(unsigned long int);
	}
	while (ws != end)
		*(wd++) = *(ws++);

	return (dest);
}
