/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:43:29 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/01 21:51:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_forkl(t_philo *p)
{
	return (p->fork_l != NULL && pthread_mutex_lock(p->fork_l) == 0);
}

bool	take_forkr(t_philo *p)
{
	return (p->fork_r != NULL && pthread_mutex_lock(p->fork_r) == 0);
}

bool	put_forkl(t_philo *p)
{
	return (p->fork_l != NULL && pthread_mutex_unlock(p->fork_l) == 0);
}

bool	put_forkr(t_philo *p)
{
	return (p->fork_r != NULL && pthread_mutex_unlock(p->fork_r) == 0);
}

bool	put_forks(t_philo *p)
{
	bool	result;

	result = put_forkl(p);
	if (!put_forkr(p))
		result = false;
	return (result);
}
