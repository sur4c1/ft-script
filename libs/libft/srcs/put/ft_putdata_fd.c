/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdata_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:59:43 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 16:03:30 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include "ft_check.h"
#include "ft_printf.h"

void	ft_putdata_fd(void *data, size_t len, int fd)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			j;

	ptr = (unsigned char *)data;
	i = 0;
	while (i < len)
	{
		while (j < 16 && i + j < len)
			ft_printf("%02x ", 0xFF & ptr[i + j++]);
		while (j++ < 16)
			ft_printf("   ");
		ft_printf("| ");
		for (ssize_t j = 0; j < 16 && i + j < len; j++)
			ft_printf("%c", ft_isprint(ptr[i + j]) ? ptr[i + j] : '.');
		ft_printf("\n");
		i += 16;
	}
}
