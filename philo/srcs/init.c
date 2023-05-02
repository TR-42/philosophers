/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:49:51 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/02 11:10:05 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - pthread_mutex_init
// - PTHREAD_MUTEX_INITIALIZER
#include <pthread.h>

// - bool
#include <stdbool.h>

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

static bool	_init_philo(t_philo *p, t_app *d, size_t i)
{
	d->forks[i] = (t_mtx){0};
	if (pthread_mutex_init(d->forks + i, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(p->cnt_lck), NULL) != 0)
	{
		pthread_mutex_destroy(d->forks + i);
		return (false);
	}
	if (pthread_mutex_init(&(p->stat_lck), NULL) != 0)
	{
		pthread_mutex_destroy(d->forks + i);
		pthread_mutex_destroy(&(p->cnt_lck));
		return (false);
	}
	p->d = d;
	p->num = i + 1;
	p->state = thinking;
	p->fork_l = d->forks + i;
	if (i == (d->philo_cnt - 1))
		p->fork_r = d->forks;
	else
		p->fork_r = d->forks + i + 1;
	return (true);
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
		if (_init_philo(d->philos + i, d, i) != true)
			return (print_err_dispose_mem_mtx("mutex init failed", d, i));
		i++;
	}
	return (0);
}

int	_t_app_init(t_app *d, int argc, const char *argv[])
{
	if (argc != 5 && argc != 6)
		return (print_err("usage: "
				"philo philo_cnt die_ms eat_ms sleep_ms [eat_quota]"));
	if (!_set(argv[1], &(d->philo_cnt)) || !_set(argv[2], &(d->die_ms))
		|| !_set(argv[3], &(d->eat_ms)) || !_set(argv[4], &(d->sleep_ms))
		|| (argc == 6 && !_set(argv[5], &(d->eat_quota))))
		return (print_err("Invalid argument format (Parse Error)"));
	if (d->philo_cnt <= 0 || d->die_ms <= 0 || d->eat_ms <= 0
		|| d->sleep_ms <= 0 || d->philo_cnt == UINTPTR_MAX)
		return (print_err("Invalid argument (some argument out of range)"));
	d->is_noquota = argc != 6;
	d->philos = ft_calloc(d->philo_cnt, sizeof(t_philo));
	d->forks = ft_calloc_nofill(d->philo_cnt, sizeof(t_mtx));
	if (d->philos == NULL || d->forks == NULL)
		return (print_err_dispose_mem("malloc failed", d));
	return (_t_app_init_philo_mutex(d));
}
