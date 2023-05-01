/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_eat_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:40:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/02 01:04:04 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_eat_cnt(t_philo *p, size_t v)
{
	int	result;

	result = pthread_mutex_lock(&(p->stat_lck));
	p->eaten_count = v;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
}

void	inc_eat_cnt(t_philo *p)
{
	int	result;

	result = pthread_mutex_lock(&(p->stat_lck));
	if (p->d->is_noquota || p->eaten_count < p->d->eat_quota)
		(p->eaten_count)++;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
}

size_t	get_eat_cnt(t_philo *p)
{
	int		result;
	size_t	v;

	result = pthread_mutex_lock(&(p->stat_lck));
	v = p->eaten_count;
	if (result == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (v);
}
