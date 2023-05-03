/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:43:29 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/03 23:42:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>

#include "philo.h"
#include "fork_manager_utils.h"

static bool	_try_l(t_philo *p, bool *lfork, bool rfork, t_tv *now)
{
	if (*lfork == true)
		return (true);
	*lfork = _take_fork_l(p, rfork);
	if (gettimeofday(now, NULL) != 0)
		return (put_forks(p) * _state(p, err) * 0);
	if (is_sim_end(p, now))
		return (put_forks(p) * 0);
	if (*lfork && !print_log(p->d, *now, p->num, take_a_fork_l))
		return (put_forks(p) * _state(p, err) * 0);
	return (true);
}

static bool	_try_r(t_philo *p, bool *rfork, bool lfork, t_tv *now)
{
	if (*rfork == true)
		return (true);
	*rfork = _take_fork_r(p, lfork);
	if (gettimeofday(now, NULL) != 0)
		return (put_forks(p) * _state(p, err) * 0);
	if (is_sim_end(p, now))
		return (put_forks(p) * 0);
	if (*rfork && !print_log(p->d, *now, p->num, take_a_fork_r))
		return (put_forks(p) * _state(p, err) * 0);
	return (true);
}

bool	take_forks(t_philo *p, t_tv *now)
{
	bool	lfork;
	bool	rfork;

	lfork = false;
	rfork = false;
	while (!lfork || !rfork)
	{
		if (_try_l(p, &lfork, rfork, now) != true)
			return (false);
		if (!lfork)
			usleep(5);
		if (_try_r(p, &rfork, lfork, now) != true)
			return (false);
		if (!rfork)
			usleep(5);
	}
	return (true);
}

bool	put_forks(t_philo *p)
{
	size_t	i;
	int		ret;

	i = _fork_index(p, -1);
	ret = pthread_mutex_lock(p->d->forks + i);
	if (p->d->fork_holder[i] == p->num)
		p->d->fork_holder[i] = 0;
	if (ret == 0)
		pthread_mutex_unlock(p->d->forks + i);
	i = _fork_index(p, 1);
	ret = pthread_mutex_lock(p->d->forks + i);
	if (p->d->fork_holder[i] == p->num)
		p->d->fork_holder[i] = 0;
	if (ret == 0)
		pthread_mutex_unlock(p->d->forks + i);
	return (true);
}
