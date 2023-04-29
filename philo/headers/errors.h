/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:40:19 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/30 01:08:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// - size_t
# include <stddef.h>

# include "philo.h"

int	print_err(const char *msg);
int	print_err_num(const char *msg, size_t philo_num);
int	print_err_dispose_mem(const char *msg, t_app *d);
int	print_err_dispose_mem_mtx(const char *msg, t_app *d, size_t mtx_cnt);

#endif
