/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:22:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/04 00:35:37 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - gettimeofday
#include <sys/time.h>

// - usleep
#include <unistd.h>

#include "ft_math.h"
#include "philo.h"

bool	sleeper(t_tv target, t_tv *now)
{
	useconds_t	sleep_us;

	if (now == NULL)
		return (false);
	while (gettimeofday(now, NULL) == 0)
	{
		if (t_tv_ispassed(now, &target))
			return (true);
		if ((target.tv_sec - now->tv_sec) > 10)
			sleep_us = 10 * 1000 * 1000;
		else
			sleep_us = (target.tv_sec - now->tv_sec) * 500000
				+ ((long)(target.tv_usec) - now->tv_usec) / 2;
		if (usleep(sleep_us) != 0)
			return (false);
	}
	return (false);
}

bool	t_tv_addms(t_tv *target, size_t ms)
{
	int	target_ms;
	int	s_overflow;

	target_ms = target->tv_usec / 1000;
	s_overflow = (ms + target_ms) / 1000;
	if (!can_addl(target->tv_sec, s_overflow))
		return (false);
	target->tv_usec = ((ms + target_ms) % 1000) * 1000;
	target->tv_sec += s_overflow;
	return (true);
}

bool	t_tv_ispassed(const t_tv *now, const t_tv *target)
{
	int	now_ms;
	int	target_ms;

	now_ms = now->tv_usec / 1000;
	target_ms = target->tv_usec / 1000;
	return (now->tv_sec > target->tv_sec
		|| (now->tv_sec == target->tv_sec
			&& now_ms >= target_ms));
}
