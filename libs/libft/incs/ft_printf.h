/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:43:37 by bguyot            #+#    #+#             */
/*   Updated: 2025/09/23 17:27:04 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#ifdef ALLOW_MALLOC
#ifdef ALLOW_FWRITE
int ft_printf(const char *restrict format, ...)
	__attribute__((format(printf, 1, 2)));
int ft_fprintf(FILE *restrict stream,
			   const char *restrict format, ...)
	__attribute__((format(printf, 2, 3)));
#endif
int ft_dprintf(int fd,
			   const char *restrict format, ...)
	__attribute__((format(printf, 2, 3)));
int ft_sprintf(char *restrict str,
			   const char *restrict format, ...)
	__attribute__((format(printf, 2, 3)));
int ft_snprintf(char str[], size_t size,
				const char *restrict format, ...)
	__attribute__((format(printf, 3, 4)));
#endif
