/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:15:36 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/03 19:16:41 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_MANAGER_UTILS_H
# define FORK_MANAGER_UTILS_H

# include "philo.h"

size_t	_fork_index(t_philo *p, int mode);
bool	_take_fork_l(t_philo *p, bool take_anyway);
bool	_take_fork_r(t_philo *p, bool take_anyway);

#endif
