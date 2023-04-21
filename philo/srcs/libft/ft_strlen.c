/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:42:59 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/21 23:49:56 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <errno.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		errno = EFAULT;
	else
		while (*(str++) != '\0')
			len++;
	return (len);
}

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		errno = EFAULT;
	else
		while (len < maxlen && *(str++) != '\0')
			len++;
	return (len);
}
