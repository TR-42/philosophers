/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:36:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/04 00:44:18 by kfujita          ###   ########.fr       */
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
	if (p->state != dead && p->state != err && p->state != ended)
	{
		if (t_tv_addms(&tv, p->d->die_ms) != true)
			stat = err;
		p->deadline = tv;
		p->state = stat;
	}
	else
		stat = p->state;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (stat);
}

static bool	philo_eat(t_philo *p, t_tv *tv)
{
	bool	success;

	if (take_forks(p, tv) != true)
		return (false);
	success = print_log(p->d, *tv, p->num, _set_last_eat(p, *tv));
	success = (success && t_tv_addms(tv, p->d->eat_ms));
	if (!success)
		_state(p, err);
	else if (!is_sim_end(p, tv))
		success = (sleeper(*tv, tv) || _state(p, err) * 0);
	return (put_forks(p) && success);
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
	{
		if (gettimeofday(&tv, NULL) != 0
			|| !t_tv_addms(&tv, p->d->eat_ms))
			return ((void *)(_state(p, err) * (size_t)0));
		if (is_sim_end(p, &tv))
			return (NULL);
		if (!sleeper(tv, &tv))
			return ((void *)(_state(p, err) * (size_t)0));
	}
	while (true)
	{
		if (!philo_eat(p, &tv))
			break ;
		inc_eat_cnt(p);
		if (!philo_action(p, &tv))
			break ;
	}
	return (NULL);
}
