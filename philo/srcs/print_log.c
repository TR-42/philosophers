/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:49:36 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/23 22:31:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - printf
#include <stdio.h>

#include "philo.h"

bool	print_log(t_app *d, t_timeval time, size_t num, t_philo_state state)
{
	int			ret;
	const char	*s_state;

	s_state = "UNKNOWN STATE";
	if (state == take_a_fork)
		s_state = "has taken a fork";
	else if (state == eating)
		s_state = "is eating";
	else if (state == thinking)
		s_state = "is thinking";
	else if (state == sleeping)
		s_state = "is sleeping";
	else if (state == dead)
		s_state = "died";
	if (pthread_mutex_lock(&(d->print_lock)) != 0)
		return (false);
	ret = printf("%ld%04ld %zu %s\n",
			time.tv_sec, time.tv_usec / 1000l, num, s_state);
	return (pthread_mutex_unlock(&(d->print_lock)) == 0 && ret > 0);
}
