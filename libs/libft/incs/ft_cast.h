/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:32:38 by bguyot            #+#    #+#             */
/*   Updated: 2025/08/26 16:54:02 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAST_H
#define FT_CAST_H

#include "ft_buff.h"
#include "ft_check.h"
#include "ft_memory.h"
#include "ft_string.h"
#include <stddef.h>

/* Return the number representing by str, skiping the firsts white spaces */
int
ft_atoi(const char *str);
long
ft_atol(const char *str);
short
ft_atos(const char *str);
unsigned int
ft_atou(const char *str);
unsigned long
ft_atoul(const char *str);
unsigned short
ft_atous(const char *str);

/* Return the string representation of the integer n
** (NULL if allocation fails) */
char *
ft_itoa(int n);

/* Return the string representation of unsigned integer n
** (NULL if allocation fails) */
char *
ft_utoa(unsigned int n);

/* Return the string representation of unsigned int n, in the given base
** (NULL if allocation fails) */
char *
ft_utoa_base(unsigned int nb, char *base);

/* Return the string representation of unsigned long n, in the given base
** (NULL if allocation fails) */
char *
ft_ultoa_base(unsigned long nb, char *base);

/* Return the upper conterpart of c if c is a lower letter, c otherwise */
int
ft_toupper(int c);

/* Return the lower conterpart of c if c is a upper letter, c otherwise */
int
ft_tolower(int c);

/* Return a buffer with the same content than str */
t_buff *
ft_atobuf(char *str);

#endif
