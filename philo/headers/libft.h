/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:41:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/04/30 00:59:20 by kfujita          ###   ########.fr       */
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

void	ft_swap(void *a, void *b, size_t bytes);

int		ft_ultoa(unsigned long value, char *buf,
			unsigned char base, bool is_upper);

#endif
