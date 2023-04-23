/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:39 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/24 00:44:28 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - pthread_mutex_init
// - PTHREAD_MUTEX_INITIALIZER
#include <pthread.h>

// - bool
#include <stdbool.h>

// - UINTPTR_MAX
#include <stdint.h>

// - malloc
// - free
#include <stdlib.h>

#include "errors.h"
#include "libft.h"
#include "philo.h"

static bool	_set(const char *str, size_t	*variable)
{
	*variable = ft_atop(str, NULL);
	return (errno == 0);
}

// f[0] p[0] f[1] p[1] ... f[LAST] p[LAST] f[0]
static int	_t_app_init_philo_mutex(t_app *d)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&(d->print_lock), NULL) != 0)
		return (print_err_dispose_mem("mutex for log-print init failed", d));
	while (i < d->philo_cnt)
	{
		d->forks[i] = (t_mtx){0};
		if (pthread_mutex_init(d->forks + i, NULL) != 0)
			return (print_err_dispose_mem_mtx("mutex init failed", d, i));
		d->philos[i].d = d;
		d->philos[i].num = i + 1;
		d->philos[i].fork_l = d->forks + i;
		if (i == (d->philo_cnt - 1))
			d->philos[i].fork_r = d->forks;
		else
			d->philos[i].fork_r = d->forks + i + 1;
		i++;
	}
	return (0);
}

static int	_t_app_init(t_app *d, int argc, const char *argv[])
{
	if (argc != 5 && argc != 6)
		return (print_err("usage: "
				"philo philo_cnt die_ms eat_ms sleep_ms [eat_quota]"));
	if (!_set(argv[1], &(d->philo_cnt)) || !_set(argv[2], &(d->die_ms))
		|| !_set(argv[3], &(d->eat_ms)) || !_set(argv[4], &(d->sleep_ms))
		|| (argc == 6 && !_set(argv[5], &(d->eat_quota))))
		return (print_err("Invalid argument format (Parse Error)"));
	if (d->philo_cnt <= 0 || d->die_ms <= 0 || d->philo_cnt == UINTPTR_MAX)
		return (print_err("Invalid argument (some argument out of range)"));
	d->is_noquota = argc != 6;
	d->philos = ft_calloc_nofill(d->philo_cnt, sizeof(t_philo));
	d->forks = ft_calloc_nofill(d->philo_cnt, sizeof(t_mtx));
	if (d->philos == NULL || d->forks == NULL)
		return (print_err_dispose_mem("malloc failed", d));
	return (_t_app_init_philo_mutex(d));
}

int	main(int argc, const char *argv[])
{
	t_app	d;
	int		ret;

	ret = _t_app_init(&d, argc, argv);
	if (ret != 0 || d.eat_quota == 0)
		return (ret);
	print_err_dispose_mem_mtx(NULL, &d, d.philo_cnt);
	return (0);
}
