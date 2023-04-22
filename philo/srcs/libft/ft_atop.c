/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:36:00 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/22 18:53:46 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - UINTPTR_MAX
#include <stdint.h>

#include "libft.h"

size_t	ft_atop(const char *str, const char **endptr)
{
	size_t	value;

	value = 0;
	if (endptr == NULL)
		endptr = &str;
	*endptr = str;
	if (str == NULL || !ft_isdigit(*str))
		errno = EFAULT;
	else
	{
		while (value != UINTPTR_MAX && ft_isdigit(**endptr))
		{
			if (can_mulp(value, 10) && can_add(value * 10, **endptr - '0'))
				value = (value * 10) + (**endptr - '0');
			else
			{
				errno = ERANGE;
				value = UINTPTR_MAX;
			}
			*endptr += 1;
		}
	}
	return (value);
}
