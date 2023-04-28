/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:36:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/28 23:48:18 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

// - gettimeofday
#include <sys/time.h>

#include "libft.h"
#include "philo.h"

t_pstat	_state(t_philo *p, t_pstat state)
{
	int	result;

	if (state == unknown)
	{
		result = pthread_mutex_lock(&(p->stat_lck));
		state = p->state;
	}
	else
	{
		result = pthread_mutex_lock(&(p->stat_lck));
		p->state = state;
	}
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (state);
}

static t_pstat	_set_last_eat(t_philo *p, t_tv tv)
{
	int	result;

	result = pthread_mutex_lock(&(p->stat_lck));
	tv.tv_sec += p->d->die_ms / 1000;
	tv.tv_usec += (p->d->die_ms % 1000) * 1000;
	p->deadline = tv;
	p->state = eating;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (eating);
}

static bool	philo_eat(t_philo *p, t_tv *tv)
{
	bool	success;

	if (pthread_mutex_lock(p->fork_l) != 0)
		return (false);
	if (gettimeofday(tv, NULL) != 0)
		return (pthread_mutex_unlock(p->fork_l) >= 0);
	if (t_tv_ispassed(tv, &(p->deadline)))
		return (pthread_mutex_unlock(p->fork_l) != 0);
	if (!print_log(p->d, *tv, p->num, take_a_fork_l)
		|| pthread_mutex_lock(p->fork_r))
		return (pthread_mutex_unlock(p->fork_l) >= 0);
	success = gettimeofday(tv, NULL) == 0;
	if (success && t_tv_ispassed(tv, &(p->deadline)))
		return (pthread_mutex_unlock(p->fork_l)
			* pthread_mutex_unlock(p->fork_r) * 0);
	success = (success && print_log(p->d, *tv, p->num, take_a_fork_r));
	success = (success && print_log(p->d, *tv, p->num, _set_last_eat(p, *tv)));
	success = (success && gettimeofday(tv, NULL) != 0);
	if (success && !t_tv_ispassed(tv, &(p->deadline)))
		success = sleeper(*tv, tv);
	(void)(pthread_mutex_unlock(p->fork_l) + pthread_mutex_unlock(p->fork_r));
	return (success);
}

static bool	philo_action(t_philo *p, t_tv *tv)
{
	if (!is_sim_end_or_set_state(p, sleeping)
		|| !print_log(p->d, *tv, p->num, sleeping)
		|| !t_tv_addms(tv, p->d->sleep_ms))
		return (false);
	if (t_tv_ispassed(tv, &(p->deadline)))
		return (true);
	if (!sleeper(*tv, tv))
		return (false);
	return (print_log(p->d, *tv, p->num, thinking));
}

void	*philo_soul(void *_p)
{
	t_philo	*p;
	t_tv	tv;
	size_t	count;

	p = (t_philo *)_p;
	if ((p->num % 2) == 0)
		ft_swap(&(p->fork_l), &(p->fork_r), sizeof(t_mtx *));
	count = 0;
	while (p->d->is_noquota || count++ < p->d->eat_quota)
	{
		if (!philo_eat(p, &tv) || !philo_action(p, &tv))
		{
			_state(p, err);
			break ;
		}
	}
	return (NULL);
}
