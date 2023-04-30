/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:39 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 00:50:25 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "philo.h"

int	main(int argc, const char *argv[])
{
	t_app	d;
	int		ret;

	ret = _t_app_init(&d, argc, argv);
	if (ret != 0 || d.eat_quota == 0)
		return (ret);
	ret = start_simulation(&d);
	if (ret == 0)
		ret = monitor_state(&d);
	if (ret == 0)
		ret = end_simulation(&d);
	print_err_dispose_mem_mtx(NULL, &d, d.philo_cnt);
	return (0);
}
