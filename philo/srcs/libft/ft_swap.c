/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:57:34 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/24 00:24:58 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_ft_swap(unsigned char *a, unsigned char *b, size_t bytes)
{
	unsigned char	tmp;

	if (a == NULL || b == NULL || a == b)
		return ;
	while (0 < bytes)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
		a++;
		b++;
		bytes--;
	}
}

void	ft_swap(void *a, void *b, size_t bytes)
{
	_ft_swap(a, b, bytes);
}
