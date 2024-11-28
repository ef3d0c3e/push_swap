/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "printf_args.h"
#include <unistd.h>

static int	_strlen(const char *s)
{
	if (s)
		return (__printf_strlen(s));
	return (__printf_strlen("(null)"));
}

int	__printf_print_string(int fd, struct s_printf_fmt *fmt, const char *s)
{
	int	w;
	int	width;

	if (!fmt && s)
		return (write(fd, s, _strlen(s)));
	else if (!fmt)
		return (write(fd, "(null)", 6));
	if (fmt->has_precision)
		width = __printf_min(_strlen(s), fmt->precision);
	else
		width = _strlen(s);
	w = 0;
	if (fmt->padding == PRINTF_PADDING_LEFT)
		w += __printf_pad(fd, ' ', fmt->width
				- __printf_min(width, fmt->precision));
	if (s)
		w += write(fd, s, width);
	else
		w += write(fd, &"      (null)"[6 * !s], 6);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
