/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 00:30:14 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/30 00:59:04 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - NULL
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char	_get_char(unsigned char value, unsigned char base, bool is_upper)
{
	if (base <= value)
		return (0);
	if (value < 10)
		return (value + '0');
	else
		return (value - 10 + 'A' + (('a' - 'A') * !is_upper));
}

// buf length should be more than 20
// this function will not terminate with NULL char
int	ft_ultoa(unsigned long value, char *buf, unsigned char base, bool is_upper)
{
	int	ret;
	int	len;
	int	tmp;

	if (base < 2 || 36 < base || buf == NULL)
		return (-1);
	buf[0] = _get_char(value, base, is_upper);
	if (value < base)
		return (1);
	len = 0;
	while (value != 0)
	{
		tmp = value % base;
		value /= base;
		buf[len++] = _get_char(tmp, base, is_upper);
	}
	ret = len;
	while (0 < --len)
	{
		tmp = buf[0];
		buf[0] = buf[len];
		buf[len--] = tmp;
		buf += 1;
	}
	return (ret);
}
