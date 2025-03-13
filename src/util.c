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
	while (end - ws >= (long int) sizeof(unsigned long int))
	{
		*(unsigned long int *)wd = *(const unsigned long int *)ws;
		wd += sizeof(unsigned long int);
		ws += sizeof(unsigned long int);
	}
	while (ws != end)
		*(wd++) = *(ws++);
	return (dest);
}

float
	clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	else if (x > max)
		return (max);
	return (x);
}

float
	approx_exp(float x)
{
	return ((362880 + x * (362880 + x * (181440 + x * (60480 + x * (15120 + x
							* (3024 + x * (504 + x * (72 + x * (9 + x)))))))))
		* 2.75573192e-6);
}
