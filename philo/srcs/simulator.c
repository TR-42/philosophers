/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:21:31 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/27 23:12:57 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "errors.h"

int	start_simulation(t_app *d)
{
	size_t	i;
	size_t	tmp;

	if (gettimeofday(&(d->start), NULL) != 0)
		return (print_err("Cannot set Start Time."));
	i = 0;
	while (i < d->philo_cnt)
	{
		if (pthread_create(&(d->philos[i].soul), NULL,
				philo_soul, d->philos + i) != 0)
		{
			tmp = i;
			while (0 < i--)
				_state(d->philos + i, err);
			while (i < tmp)
				pthread_join(d->philos[i].soul, NULL);
			return (print_err("Thread creation failed."));
		}
		i++;
	}
	return (0);
}

bool	is_sim_end_or_set_state(t_philo *p, t_pstat state)
{
	int		ret;
	bool	is_ended;
	t_tv	tv;

	is_ended = false;
	ret = pthread_mutex_lock(&(p->stat_lck));
	if (p->state == dead || p->state == err || p->state == ended)
		is_ended = true;
	else
	{
		if (gettimeofday(&tv, NULL) != 0)
			is_ended = (0 <= print_err("GetTimeOfDay failed."));
		else if (t_tv_ispassed(&tv, &(p->deadline)))
		{
			is_ended = true;
			print_log(p->d, tv, p->num, dead);
		}
		else if (state != unknown)
			p->state = state;
	}
	p->state = ended;
	if (ret == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (is_ended);
}

int	monitor_state(t_app *d)
{
	size_t	i;

	i = 0;
	while (true)
	{
		i = 0;
		while (i < d->philo_cnt)
			if (is_sim_end_or_set_state(d->philos + i++, unknown))
				return (0);
	}
	return (0);
}

int	end_simulation(t_app *d)
{
	size_t	i;

	i = 0;
	while (i < d->philo_cnt)
		_state(d->philos + i++, ended);
	i = 0;
	while (i < d->philo_cnt)
		pthread_join(d->philos[i].soul, NULL);
	return (0);
}
