/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 21:08:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "errors.h"

bool	is_sim_end(t_philo *p, const t_tv *now)
{
	int		ret;
	bool	is_ended;

	ret = pthread_mutex_lock(&(p->stat_lck));
	if (p->state == ended)
		return (true);
	is_ended = is_sim_end_nolock(p, now, false);
	if (ret == 0)
		pthread_mutex_unlock(&(p->stat_lck));
	return (is_ended);
}

bool	is_sim_end_nolock(t_philo *p, const t_tv *now, bool do_print)
{
	bool	is_ended;

	is_ended = (p->state == dead || p->state == err || p->state == ended);
	if (!is_ended)
	{
		is_ended = t_tv_ispassed(now, &(p->deadline));
		if (is_ended && do_print)
			print_log(p->d, *now, p->num, dead);
	}
	if (do_print && p->state == err)
		print_err_num("Unknown error occured", p->num);
	return (is_ended);
}

bool	is_sim_end_or_set_state(t_philo *p, t_pstat state)
{
	int		ret;
	bool	is_ended;
	t_tv	tv;

	ret = pthread_mutex_lock(&(p->stat_lck));
	if (p->state == ended)
		return (true);
	if (gettimeofday(&tv, NULL) != 0)
		is_ended = (0 <= print_err("GetTimeOfDay failed."));
	else
		is_ended = is_sim_end_nolock(p, &tv, state == unknown);
	if (state == unknown && is_ended)
		p->state = ended;
	(void)(ret == 0 && pthread_mutex_unlock(&(p->stat_lck)));
	return (is_ended);
}
