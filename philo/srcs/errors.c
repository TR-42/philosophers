/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:40:09 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/24 00:43:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

#include "libft.h"

// - free
#include <stdlib.h>

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

int	print_err_dispose_mem(const char *msg, t_app *d)
{
	print_err(msg);
	free(d->philos);
	free(d->forks);
	d->philos = NULL;
	d->forks = NULL;
	return (1);
}

int	print_err_dispose_mem_mtx(const char *msg, t_app *d, size_t mtx_cnt)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&(d->print_lock));
	if (d->forks != NULL)
		while (i < mtx_cnt)
			pthread_mutex_destroy(d->forks + i++);
	return (print_err_dispose_mem(msg, d));
}
