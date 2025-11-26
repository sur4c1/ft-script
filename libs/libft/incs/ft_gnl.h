/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:39:42 by bguyot            #+#    #+#             */
/*   Updated: 2024/12/17 17:15:34 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include "ft_memory.h"
#include "ft_string.h"
#include "ft_def.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

typedef struct _s_gnl
{
	char	buff[FD_MAX][BUFFER_SIZE];
	size_t	remainder;
}	_t_gnl;

/**
 * @brief Read the file descriptor fd and return a allocated string containing the next line
 * @note The function will return NULL if the file descriptor is invalid
 * @param fd The file descriptor to read
 * @return The next line of the file descriptor, without the '\\n' character
 * @note Must be freed by the user
 * @note May be used on multiple file descriptors at the same time
 */
char	*ft_gnl(int fd);

#endif
