/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

static int	write_int(int fd, unsigned int x)
{
	int	written;

	written = 0;
	if (x >= 10)
		written = write_int(fd, x / 10);
	return (written + __printf_print_char(fd, 0,
			(x % 10) + '0'));
}

static int	log10u(unsigned int x)
{
	int	cnt;

	cnt = 0;
	while (x)
	{
		x /= 10;
		++cnt;
	}
	return (!cnt + cnt);
}

static char	get_sign(struct s_printf_fmt *fmt)
{
	if (fmt->force_sign)
		return ('+');
	return ('\0');
}

int	__printf_print_unsigned(int fd, struct s_printf_fmt *fmt, unsigned int x)
{
	int		width;
	char	sign;
	int		w;

	width = log10u(x);
	sign = get_sign(fmt);
	w = 0;
	if (fmt->padding == PRINTF_PADDING_LEFT)
		w += __printf_pad(fd, ' ', fmt->width
				- __printf_max(width, fmt->precision) - (sign != 0));
	if (sign)
		w += write(fd, &sign, 1);
	w += __printf_pad(fd, '0', fmt->precision - width);
	if (fmt->padding == PRINTF_PADDING_ZEROS)
		w += __printf_pad(fd, '0', fmt->width - w - width);
	w += write_int(fd, x);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
