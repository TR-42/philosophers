/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:36:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/28 23:10:07 by kfujita          ###   ########.fr       */
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

static bool	philo_action(t_philo *p)
{
	t_tv	tv;
	bool	success;

	if (pthread_mutex_lock(p->fork_l) != 0)
		return (false);
	if (gettimeofday(&tv, NULL) || t_tv_ispassed(&tv, &(p->deadline))
		|| print_log(p->d, tv, p->num, take_a_fork))
		return (pthread_mutex_unlock(p->fork_l) >= 0);
	if (pthread_mutex_lock(p->fork_r) && pthread_mutex_unlock(p->fork_l) >= 0)
		return (false);
	success = (gettimeofday(&tv, NULL) == 0
			&& !t_tv_ispassed(&tv, &(p->deadline))
			&& print_log(p->d, tv, p->num, take_a_fork)
			&& print_log(p->d, tv, p->num, _set_last_eat(p, tv))
			&& t_tv_addms(&tv, p->d->eat_ms)
			&& !t_tv_ispassed(&tv, &(p->deadline)) && sleeper(tv, &tv));
	(void)(pthread_mutex_unlock(p->fork_l) + pthread_mutex_unlock(p->fork_r));
	if (!success)
		return (false);
	return (is_sim_end_or_set_state(p, sleeping)
		&& print_log(p->d, tv, p->num, sleeping)
		&& t_tv_addms(&tv, p->d->sleep_ms)
		&& (t_tv_ispassed(&tv, &(p->deadline))
			|| (sleeper(tv, &tv) && print_log(p->d, tv, p->num, thinking))));
}

void	*philo_soul(void *_p)
{
	t_philo	*p;
	size_t	count;

	p = (t_philo *)_p;
	if ((p->num % 2) == 0)
		ft_swap(&(p->fork_l), &(p->fork_r), sizeof(t_mtx *));
	count = 0;
	while (p->d->is_noquota || count++ < p->d->eat_quota)
	{
		if (!philo_action(p))
		{
			_state(p, err);
			break ;
		}
	}
	return (NULL);
}
