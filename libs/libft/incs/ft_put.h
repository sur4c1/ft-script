/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:49:24 by bguyot            #+#    #+#             */
/*   Updated: 2025/10/20 22:10:08 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
#define FT_PUT_H

#include "ft_string.h"
#include <unistd.h>

/* Write the char c in the given fd */
void
ft_putchar_fd(char c, int fd);
#define ft_putchar(c) ft_putchar_fd(c, 1)

/* Write the string s in the given fd */
void
ft_putstr_fd(char *s, int fd);
#define ft_putstr(c) ft_putstr_fd(c, 1)

/* Write the string s in the given fd with a line break */
void
ft_putendl_fd(char *s, int fd);
#define ft_putendl(c) ft_putendl_fd(c, 1)

/* Write a strnig representing n in the given fd */
void
ft_putnbr_fd(int n, int fd);
#define ft_putnbr(c) ft_putnbr_fd(c, 1)

/* Write all the string of tab (NULL terminated) into fd */
void
ft_puttab_fd(char **tab, int fd);
#define ft_puttab(c) ft_putchatab(c, 1)

/**
 * @brief Write the data of size size in the given fd
 * @note The data is printed in hexadecimal and ascii
 */
void
ft_putdata_fd(void *data, size_t size, int fd);

#endif
