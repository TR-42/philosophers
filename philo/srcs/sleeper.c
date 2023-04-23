/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:22:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/24 00:23:26 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - gettimeofday
#include <sys/time.h>

// - usleep
#include <unistd.h>

#include "philo.h"

bool	sleeper(t_tv target, t_tv *result)
{
	useconds_t	sleep_us;

	if (result == NULL)
		return (false);
	while (gettimeofday(result, NULL) == 0)
	{
		if (target.tv_sec < result->tv_sec || (target.tv_sec == result->tv_sec
				&& target.tv_usec <= result->tv_usec))
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
