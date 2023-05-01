/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:21:31 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 20:44:16 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "errors.h"

int	start_simulation(t_app *d)
{
	size_t	i;
	size_t	tmp;

	if (gettimeofday(&(d->first_dl), NULL) != 0
		|| !t_tv_addms(&(d->first_dl), d->die_ms))
		return (print_err("Cannot set Start Time."));
	i = 0;
	while (i < d->philo_cnt)
	{
		d->philos[i].deadline = d->first_dl;
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

int	monitor_state(t_app *d)
{
	size_t	i;
	bool	simend;

	i = 0;
	simend = false;
	while (!simend)
	{
		i = 0;
		simend = !(d->is_noquota);
		while (i < d->philo_cnt)
		{
			if (is_sim_end_or_set_state(d->philos + i, unknown))
				return (0);
			simend = (simend && (d->eat_quota <= get_eat_cnt(d->philos + i)));
			i++;
		}
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
		pthread_join(d->philos[i++].soul, NULL);
	return (0);
}
