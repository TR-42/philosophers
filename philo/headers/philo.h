/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:24 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/21 23:39:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// - size_t
# include <stddef.h>

// philo_cnt: number_of_philosophers
// die_ms: time_to_die [ms]
// eat_ms: time_to_eat [ms]
// sleep_ms: time_to_sleep [ms]
// eat_qupta: (opt) number_of_times_each_philosopher_must_eat
typedef struct s_app
{
	size_t	philo_cnt;
	size_t	die_ms;
	size_t	eat_ms;
	size_t	sleep_ms;
	size_t	eat_quota;
}	t_app;

#endif
