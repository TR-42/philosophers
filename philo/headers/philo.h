/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:24 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/24 00:33:34 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

// - bool
# include <stdbool.h>

// - size_t
# include <stddef.h>

// - timeval
# include <sys/time.h>

typedef pthread_t		t_thrd;
typedef pthread_mutex_t	t_mtx;
typedef struct s_app	t_app;
typedef struct timeval	t_tv;

typedef enum e_philo_state
{
	unknown,
	take_a_fork,
	eating,
	thinking,
	sleeping,
	dead,
	err,
}	t_philo_state;
typedef t_philo_state	t_pstat;

typedef struct s_philo
{
	t_app	*d;
	size_t	num;
	t_thrd	soul;
	t_tv	deadline;
	t_pstat	state;
	t_mtx	stat_lck;
	t_mtx	*fork_l;
	t_mtx	*fork_r;
}	t_philo;

// philo_cnt: number_of_philosophers
// die_ms: time_to_die [ms]
// eat_ms: time_to_eat [ms]
// sleep_ms: time_to_sleep [ms]
// eat_qupta: (opt) number_of_times_each_philosopher_must_eat
struct s_app
{
	size_t	philo_cnt;
	size_t	die_ms;
	size_t	eat_ms;
	size_t	sleep_ms;
	size_t	eat_quota;
	bool	is_noquota;
	t_tv	start;
	t_mtx	print_lock;
	t_philo	*philos;
	t_mtx	*forks;
};

bool	print_log(t_app *d, t_tv time, size_t num, t_philo_state state);

bool	sleeper(t_tv target, t_tv *result);
bool	t_tv_addms(t_tv *target, size_t ms);

#endif
