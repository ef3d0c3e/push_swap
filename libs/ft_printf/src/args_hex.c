/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf_args.h"
#include <unistd.h>

static int	write_hex(int fd, unsigned int x, int uppercase)
{
	int	written;

	written = 0;
	if (x >= 16)
		written = write_hex(fd, x / 16, uppercase);
	return (written + __printf_print_char(fd, 0,
			"0123456789abcdef0123456789ABCDEF"[16 * uppercase + (x % 16)]));
}

static int	log16u(unsigned int x)
{
	int	cnt;

	cnt = 0;
	while (x)
	{
		x /= 16;
		++cnt;
	}
	return (!cnt + cnt);
}

int	__printf_print_hex(
		int fd,
		struct s_printf_fmt *fmt,
		unsigned int x,
		int uppercase
		)
{
	int		width;
	int		w;

	width = log16u(x);
	w = 0;
	if (fmt->padding == PRINTF_PADDING_LEFT)
		w += __printf_pad(fd, ' ', fmt->width
				- __printf_max(width, fmt->precision));
	if (fmt->alternate_form && x)
		w += write(fd, &"0x0X"[uppercase * 2], 2);
	w += __printf_pad(fd, '0', fmt->precision - width);
	if (fmt->padding == PRINTF_PADDING_ZEROS)
		w += __printf_pad(fd, '0', fmt->width - w - width);
	w += write_hex(fd, x, uppercase);
	w += __printf_pad(fd, ' ', fmt->width - w);
	return (w);
}
