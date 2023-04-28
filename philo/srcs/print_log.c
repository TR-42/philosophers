/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:49:36 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/29 00:24:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - printf
#include <stdio.h>

#include "philo.h"

#ifdef DEBUG
# define TAKE_A_FORK_L ("has taken a fork (L)")
# define TAKE_A_FORK_R ("has taken a fork (R)")
#else
# define TAKE_A_FORK_L ("has taken a fork")
# define TAKE_A_FORK_R ("has taken a fork")
#endif

bool	print_log(t_app *d, t_tv time, size_t num, t_philo_state state)
{
	int			ret;
	const char	*s_state;

	s_state = "UNKNOWN STATE";
	if (state == take_a_fork_l)
		s_state = TAKE_A_FORK_L;
	else if (state == take_a_fork_r)
		s_state = TAKE_A_FORK_R;
	else if (state == eating)
		s_state = "is eating";
	else if (state == thinking)
		s_state = "is thinking";
	else if (state == sleeping)
		s_state = "is sleeping";
	else if (state == dead)
		s_state = "died";
	else
		return (false);
	if (pthread_mutex_lock(&(d->print_lock)) != 0)
		return (false);
	ret = printf("%ld%03ld %zu %s\n",
			time.tv_sec, (time.tv_usec / 1000l) % 1000, num, s_state);
	return (pthread_mutex_unlock(&(d->print_lock)) == 0 && ret > 0);
}
