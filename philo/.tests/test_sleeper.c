/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sleeper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 01:29:19 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/30 01:36:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <string.h>
#include <stdio.h>

#include "philo.h"

#define BUF_SIZE 128

static char	*_ctime(t_tv tv)
{
	char	*ts;
	time_t	t;

	t = (time_t)(tv.tv_sec);
	ts = ctime(&t);
	ts[strlen(ts) - 1] = '\0';
	return (ts);
}

static char	*_set_tv_str(t_tv tv, char *s)
{
	snprintf(s, BUF_SIZE, "%s (%03d_%03d)",
		_ctime(tv),
		(tv.tv_usec / 1000) % 1000,
		tv.tv_usec % 1000);
	return (s);
}

static void	_sleep_ms(size_t ms)
{
	char	buf[BUF_SIZE];
	t_tv	now;
	t_tv	target;

	now = (t_tv){0};
	gettimeofday(&now, NULL);
	target = now;
	t_tv_addms(&target, ms);
	printf("Target: %s (Sleep for %zu ms)\n", _set_tv_str(target, buf), ms);
	printf("%s -> ", _set_tv_str(now, buf));
	printf("(%d) -> ", sleeper(target, &now));
	puts(_set_tv_str(now, buf));
}

int	main(void)
{
	_sleep_ms(10);
	_sleep_ms(100);
	_sleep_ms(1000);
	_sleep_ms(5000);
}
