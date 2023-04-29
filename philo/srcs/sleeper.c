/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:22:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/29 17:22:41 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - gettimeofday
#include <sys/time.h>

// - usleep
#include <unistd.h>

#include "ft_math.h"
#include "philo.h"

bool	sleeper(t_tv target, t_tv *result)
{
	useconds_t	sleep_us;

	if (result == NULL)
		return (false);
	while (gettimeofday(result, NULL) == 0)
	{
		if (t_tv_ispassed(result, &target))
			return (true);
		if ((target.tv_sec - result->tv_sec) > 10)
			sleep_us = 10 * 1000 * 1000;
		else
			sleep_us = (target.tv_sec - result->tv_sec) * 500000
				+ ((long)(target.tv_usec) - result->tv_usec) / 2;
		if (usleep(sleep_us) != 0)
			return (false);
	}
	return (false);
}

bool	t_tv_addms(t_tv *target, size_t ms)
{
	if (!can_addl(target->tv_sec, (ms / 1000) + (target->tv_usec / 1000000)))
		return (false);
	target->tv_usec = (((ms % 1000) * 1000) + target->tv_usec);
	target->tv_sec += (ms / 1000) + (target->tv_usec / 1000000);
	target->tv_usec %= 1000000;
	return (true);
}

bool	t_tv_ispassed(const t_tv *now, const t_tv *target)
{
	return (now->tv_sec > target->tv_sec
		|| (now->tv_sec == target->tv_sec
			&& now->tv_usec >= target->tv_usec));
}
