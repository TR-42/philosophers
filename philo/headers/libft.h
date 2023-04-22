/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:41:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/22 18:36:30 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// - size_t
# include <stddef.h>

# include "ft_math.h"

size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);

#endif
