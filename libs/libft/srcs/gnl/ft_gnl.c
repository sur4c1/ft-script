/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:25:13 by bguyot            #+#    #+#             */
/*   Updated: 2024/12/19 15:24:50 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"

static
size_t	find_line_len(const char *buff, size_t reminder)
{
	size_t	len;

	len = 0;
	while (len < reminder && buff[len] != '\n')
		len++;
	return (len);
}

static
char *strjoin_free(char *s1, char *s2, size_t len)
{
	char	*ret;
	char	*s_cpy;

	s_cpy = ft_strndup(s2, len);
	s_cpy[len] = '\0';
	ret = ft_strjoin(s1, s_cpy);
	free(s1);
	free(s_cpy);
	return (ret);
}

static
char *fill_next_line(int fd, _t_gnl *gnl, char *next_line)
{
	ssize_t	len;
	char	*new_line_ptr;

	new_line_ptr = ft_strnchr(gnl->buff[fd], '\n', gnl->remainder);
	while (!new_line_ptr && (len = read(fd, gnl->buff[fd], BUFFER_SIZE)) > 0)
	{
		new_line_ptr = ft_strnchr(gnl->buff[fd], '\n', len);
		if (new_line_ptr)
		{
			next_line = strjoin_free
			(
				next_line, gnl->buff[fd], new_line_ptr - gnl->buff[fd]
			);
			gnl->remainder = len - (new_line_ptr + 1 - gnl->buff[fd]);
			ft_memmove(gnl->buff[fd], new_line_ptr + 1, gnl->remainder);
		}
		else
			next_line = strjoin_free(next_line, gnl->buff[fd], len);
	}
	if (len < 0)
		return (free(next_line), NULL);
	return (next_line);
}

char	*ft_gnl(int fd)
{
	static _t_gnl	gnl;
	ssize_t			len;
	char			*next_line;

	len = find_line_len(gnl.buff[fd], gnl.remainder);
	next_line = NULL;
	if (gnl.remainder)
		next_line = ft_strndup(gnl.buff[fd], len);
	if (len == (ssize_t) gnl.remainder)
		return fill_next_line(fd, &gnl, next_line);
	gnl.remainder -= len + 1;
	ft_memmove(gnl.buff[fd], gnl.buff[fd] + len + 1, gnl.remainder);
	return (next_line);
}
