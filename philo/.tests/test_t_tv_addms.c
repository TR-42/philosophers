/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_t_tv_addms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:33:02 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/29 17:11:11 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

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

static void	_add_print(const char *s, size_t v)
{
	char	buf[BUF_SIZE];
	t_tv	tv;

	tv = (t_tv){0};
	puts(s);
	printf("%s -> ", _set_tv_str(tv, buf));
	printf("(%d) -> ", t_tv_addms(&tv, v));
	puts(_set_tv_str(tv, buf));
}

int	main(void)
{
	puts(__FILE__);
	_add_print("Add 0", 0);
	_add_print("Add 10", 10);
	_add_print("Add 1e12", 1e12 + 123456);
	return (0);
}
