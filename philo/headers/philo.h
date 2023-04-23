/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:29:24 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/23 22:07:03 by kfujita          ###   ########.fr       */
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
typedef struct timeval	t_timeval;

typedef enum e_philo_state
{
	take_a_fork,
	eating,
	thinking,
	sleeping,
	dead,
}	t_philo_state;

typedef struct s_philo
{
	t_app	*d;
	size_t	num;
	t_thrd	soul;
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
	t_mtx	print_lock;
	t_philo	*philos;
	t_mtx	*forks;
};

bool	print_log(t_app *d, t_timeval time, size_t num, t_philo_state state);

#endif
