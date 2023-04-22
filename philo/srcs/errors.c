/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:40:09 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/22 18:57:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

#include "libft.h"

// - STDERR_FILENO
// - write
#include <unistd.h>

int	print_err(const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	if (len != 0)
	{
		(write(STDERR_FILENO, msg, len) > 0 && write(STDERR_FILENO, "\n", 1));
	}
	return (1);
}
