/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:36:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 21:23:27 by kfujita          ###   ########.fr       */
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
	t_pstat	stat;
	int		result;

	stat = eating;
	result = pthread_mutex_lock(&(p->stat_lck));
	if (t_tv_addms(&tv, p->d->die_ms) != true)
		stat = err;
	p->deadline = tv;
	if (p->state != dead && p->state != err && p->state != ended)
		p->state = stat;
	else
		stat = p->state;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (stat);
}

static bool	philo_eat(t_philo *p, t_tv *tv)
{
	bool	success;

	if (pthread_mutex_lock(p->fork_l) != 0)
		return (false);
	if (gettimeofday(tv, NULL) != 0)
		return (pthread_mutex_unlock(p->fork_l) * _state(p, err) * 0);
	if (is_sim_end(p, tv))
		return (pthread_mutex_unlock(p->fork_l) * 0);
	if (!print_log(p->d, *tv, p->num, take_a_fork_l)
		|| pthread_mutex_lock(p->fork_r))
		return (pthread_mutex_unlock(p->fork_l) * _state(p, err) * 0);
	success = gettimeofday(tv, NULL) == 0;
	if (success && is_sim_end(p, tv))
		return (pthread_mutex_unlock(p->fork_l)
			* pthread_mutex_unlock(p->fork_r) * 0);
	success = (success && print_log(p->d, *tv, p->num, take_a_fork_r));
	success = (success && print_log(p->d, *tv, p->num, _set_last_eat(p, *tv)));
	success = (success && t_tv_addms(tv, p->d->eat_ms));
	if (success && !is_sim_end(p, tv))
		success = sleeper(*tv, tv);
	(void)(pthread_mutex_unlock(p->fork_l) + pthread_mutex_unlock(p->fork_r));
	return (success);
}

static bool	philo_action(t_philo *p, t_tv *tv)
{
	if (is_sim_end_or_set_state(p, sleeping))
		return (false);
	if (!print_log(p->d, *tv, p->num, sleeping)
		|| !t_tv_addms(tv, p->d->sleep_ms))
		return (_state(p, err) * 0);
	if (is_sim_end(p, tv))
		return (false);
	if (!sleeper(*tv, tv))
		return (_state(p, err) * 0);
	if (is_sim_end_or_set_state(p, thinking))
		return (false);
	if (!print_log(p->d, *tv, p->num, thinking))
		return (_state(p, err) * 0);
	return (true);
}

void	*philo_soul(void *_p)
{
	t_philo	*p;
	t_tv	tv;

	p = (t_philo *)_p;
	if ((p->num % 2) == 0)
		ft_swap(&(p->fork_l), &(p->fork_r), sizeof(t_mtx *));
	while (true)
	{
		if (!philo_eat(p, &tv))
			break ;
		inc_eat_cnt(p);
		if (t_tv_ispassed(&tv, &(p->deadline))
			|| !philo_action(p, &tv)
			|| t_tv_ispassed(&tv, &(p->deadline)))
			break ;
	}
	return (NULL);
}
