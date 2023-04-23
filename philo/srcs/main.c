/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:39 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/23 18:51:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - bool
#include <stdbool.h>

// - UINTPTR_MAX
#include <stdint.h>

#include "errors.h"
#include "libft.h"
#include "philo.h"

static bool	_set(const char *str, size_t	*variable)
{
	*variable = ft_atop(str, NULL);
	return (errno == 0);
}

static int	_t_app_init(t_app *d, int argc, const char *argv[])
{
	if (argc != 5 && argc != 6)
		return (print_err("usage: "
				"philo philo_cnt die_ms eat_ms sleep_ms [eat_quota]"));
	d->eat_quota = UINTPTR_MAX;
	if (!_set(argv[1], &(d->philo_cnt)) || !_set(argv[2], &(d->die_ms))
		|| !_set(argv[3], &(d->eat_ms)) || !_set(argv[4], &(d->sleep_ms))
		|| (argc == 6 && !_set(argv[5], &(d->eat_quota))))
		return (print_err("Invalid argument format (Parse Error)"));
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_app	d;
	int		ret;

	ret = _t_app_init(&d, argc, argv);
	if (ret != 0)
		return (ret);
	return (0);
}
