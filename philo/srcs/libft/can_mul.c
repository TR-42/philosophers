/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:29:25 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/22 19:14:02 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

#include <limits.h>
#include <stdint.h>

bool	can_mul(int a, int b)
{
	if (a == 0 || b == 0)
		return (true);
	else if ((0 < a && 0 < b) || (a < 0 && b < 0))
		return (b <= (INT_MAX / a));
	else if (b < 0)
		return ((INT_MIN / a) <= b);
	else
		return ((INT_MIN / b) <= a);
}

bool	can_mulu(unsigned int a, unsigned int b)
{
	if (a == 0 || b == 0)
		return (true);
	else
		return (b <= (UINT_MAX / a));
}

bool	can_mull(long a, long b)
{
	if (a == 0 || b == 0)
		return (true);
	else if ((0 < a && 0 < b) || (a < 0 && b < 0))
		return (b <= (LONG_MAX / a));
	else if (b < 0)
		return ((LONG_MIN / a) <= b);
	else
		return ((LONG_MIN / b) <= a);
}

bool	can_mulp(size_t a, size_t b)
{
	if (a == 0 || b == 0)
		return (true);
	else
		return (b <= (UINTPTR_MAX / a));
}