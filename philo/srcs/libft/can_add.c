/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:14:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/06 19:28:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

#include <limits.h>

bool	can_add(int a, int b)
{
	if ((a <= 0 && 0 <= b) || (b <= 0 && 0 <= a))
		return (true);
	else if (0 < a)
		return (b <= (INT_MAX - a));
	else
		return ((INT_MIN - a) <= b);
}

bool	can_addu(unsigned int a, unsigned int b)
{
	return (b <= (UINT_MAX - a));
}

bool	can_addl(long a, long b)
{
	if ((a <= 0 && 0 <= b) || (b <= 0 && 0 <= a))
		return (true);
	else if (0 < a)
		return (b <= (LONG_MAX - a));
	else
		return ((LONG_MIN - a) <= b);
}

bool	can_addp(size_t a, size_t b)
{
	return (b <= (SIZE_T_MAX - a));
}