/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:52 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/09/23 17:26:52 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__ft_printf.h"

#ifdef ALLOW_MALLOC
#ifdef ALLOW_FWRITE
int ft_printf(const char *restrict format, ...)
{
	va_list ap;
	t_buff buff;

	buff = (t_buff){0};
	va_start(ap, format);
	__ft_printf((char *)format, ap, &buff);
	va_end(ap);
	fwrite(buff.data, 1, buff.len, stdout);
	free(buff.data);
	return (buff.len);
}

int ft_fprintf(FILE *restrict stream, const char *restrict format, ...)
{
	va_list ap;
	t_buff buff;

	buff = (t_buff){0};
	va_start(ap, format);
	__ft_printf((char *)format, ap, &buff);
	va_end(ap);
	fwrite(buff.data, 1, buff.len, stream);
	free(buff.data);
	return (buff.len);
}
#else
#define ft_printf(format, ...) ft_dprintf(1, format, __VA_ARGS__)
#endif

int ft_dprintf(t_fd fd, const char *restrict format, ...)
{
	va_list ap;
	t_buff buff;

	buff = (t_buff){0};
	va_start(ap, format);
	__ft_printf((char *)format, ap, &buff);
	va_end(ap);
	write(fd, buff.data, buff.len);
	free(buff.data);
	return (buff.len);
}

int ft_sprintf(char *restrict str, const char *restrict format, ...)
{
	va_list ap;
	t_buff buff;

	buff = (t_buff){0};
	va_start(ap, format);
	__ft_printf((char *)format, ap, &buff);
	va_end(ap);
	ft_memcpy(str, buff.data, buff.len);
	free(buff.data);
	return (buff.len);
}

int ft_snprintf(char *restrict str, size_t size, const char *restrict format, ...)
{
	va_list ap;
	t_buff buff;
	size_t len;

	buff = (t_buff){0};
	va_start(ap, format);
	__ft_printf((char *)format, ap, &buff);
	va_end(ap);
	len = buff.len < size ? buff.len : size;
	ft_memcpy(str, buff.data, len);
	free(buff.data);
	return (len);
}
#endif
