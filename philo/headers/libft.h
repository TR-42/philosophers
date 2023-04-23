/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:41:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/23 18:55:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// - bool
# include <stdbool.h>

// - size_t
# include <stddef.h>

# include "ft_math.h"

size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);

bool	ft_isdigit(int c);

size_t	ft_atop(const char *str, const char **endptr);

void	*ft_calloc_nofill(size_t count, size_t size);
void	*ft_calloc(size_t count, size_t size);

#endif
