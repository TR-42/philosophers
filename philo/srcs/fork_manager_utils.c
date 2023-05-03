/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:16:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/03 23:10:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork_manager_utils.h"

// -2: left Philo's left fork
// -1: left Philo's right fork / my left fork
//  0: same sa -1
//  1: right Philo's left fork / my right fork
//  2: right Philo's right fork
size_t	_fork_index(t_philo *p, int mode)
{
	if (mode == 0 || mode == -1 || p->d->philo_cnt <= 1)
		return (p->num - 1);
	if (mode == -2)
	{
		if (p->num == 1)
			return (p->d->philo_cnt - 1);
		else
			return (p->num - 2);
	}
	if (mode == 1)
	{
		if (p->num == p->d->philo_cnt)
			return (0);
		else
			return (p->num);
	}
	if (mode == 2)
	{
		if (p->num == p->d->philo_cnt || p->num == (p->d->philo_cnt - 1))
			return (p->d->philo_cnt - p->num);
		else
			return (p->num + 1);
	}
	return (0);
}

static size_t	_take_fork_pre(t_philo *p, bool take_anyway, int mode)
{
	size_t	i;
	int		ret;
	size_t	holder;

	i = _fork_index(p, mode);
	ret = pthread_mutex_lock(p->d->forks + i);
	holder = p->d->fork_holder[i];
	if (holder == 0 && take_anyway)
		p->d->fork_holder[i] = p->num;
	(void)(ret == 0 && pthread_mutex_unlock(p->d->forks + i));
	return (holder);
	if (holder != 0)
		return (holder == p->num);
	else
		return (take_anyway);
}

bool	_take_fork_l(t_philo *p, bool take_anyway)
{
	size_t	i;
	int		ret;
	size_t	holder;

	holder = _take_fork_pre(p, take_anyway, -1);
	if (holder != 0 || (holder == 0 && take_anyway))
		return (holder == p->num || holder == 0);
	i = _fork_index(p, -2);
	ret = pthread_mutex_lock(p->d->forks + i);
	holder = p->d->fork_holder[i];
	(void)(ret == 0 && pthread_mutex_unlock(p->d->forks + i));
	if (holder == i + 1)
		return (false);
	i = _fork_index(p, -1);
	ret = pthread_mutex_lock(p->d->forks + i);
	holder = p->d->fork_holder[i];
	if (holder == 0)
		p->d->fork_holder[i] = p->num;
	(void)(ret == 0 && pthread_mutex_unlock(p->d->forks + i));
	return (holder == 0);
}

bool	_take_fork_r(t_philo *p, bool take_anyway)
{
	size_t	i;
	int		ret;
	size_t	holder;

	holder = _take_fork_pre(p, take_anyway, 1);
	if (holder != 0 || (holder == 0 && take_anyway))
		return (holder == p->num || holder == 0);
	i = _fork_index(p, 2);
	ret = pthread_mutex_lock(p->d->forks + i);
	holder = p->d->fork_holder[i];
	(void)(ret == 0 && pthread_mutex_unlock(p->d->forks + i));
	if ((p->num == p->d->philo_cnt && holder == 1)
		|| (p->num != p->d->philo_cnt && holder == p->num + 1))
		return (false);
	i = _fork_index(p, 1);
	ret = pthread_mutex_lock(p->d->forks + i);
	holder = p->d->fork_holder[i];
	if (holder == 0)
		p->d->fork_holder[i] = p->num;
	(void)(ret == 0 && pthread_mutex_unlock(p->d->forks + i));
	return (holder == 0);
}
