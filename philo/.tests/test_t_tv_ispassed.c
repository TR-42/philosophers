/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_t_tv_ispassed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 00:10:52 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/30 00:19:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philo.h"

int	main(void)
{
	t_tv	now;
	t_tv	target;

	target = (t_tv){1000, 100 * 1000};
	now = (t_tv){999, 0};
	puts(__FILE__);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	t_tv_addms(&now, 100);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	t_tv_addms(&now, 900);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	t_tv_addms(&now, 90);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	t_tv_addms(&now, 10);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	t_tv_addms(&now, 100);
	printf("%zu.%06d <> %zu.%06d => %d\n", now.tv_sec, now.tv_usec,
		target.tv_sec, target.tv_usec, t_tv_ispassed(&now, &target));
	return (0);
}
