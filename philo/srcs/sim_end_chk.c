/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 20:44:50 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "errors.h"

bool	is_sim_end_or_set_state(t_philo *p, t_pstat state)
{
	int		ret;
	bool	is_ended;
	t_tv	tv;

	ret = pthread_mutex_lock(&(p->stat_lck));
	is_ended = (p->state == dead || p->state == err || p->state == ended);
	if (!is_ended)
	{
		if (gettimeofday(&tv, NULL) != 0)
			is_ended = (0 <= print_err("GetTimeOfDay failed."));
		else if (t_tv_ispassed(&tv, &(p->deadline)))
			p->state = dead;
		else if (state != unknown)
			p->state = state;
	}
	if (state == unknown && p->state == err)
		print_err_num("Unknown error occured", p->num);
	else if (state == unknown && p->state == dead)
		print_log(p->d, tv, p->num, dead);
	if (is_ended || p->state == dead)
		p->state = ended;
	(void)(ret == 0 && pthread_mutex_unlock(&(p->stat_lck)));
	return (is_ended);
}
