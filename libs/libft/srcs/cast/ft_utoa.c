/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:22:07 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/21 05:52:09 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"

static size_t	len(unsigned int n);

char	*ft_utoa(unsigned int n)
{
	char	*res;
	size_t	size;
	size_t	tmp;

	size = len(n);
	res = malloc((size + 1) * sizeof (char));
	if (!res)
		return (NULL);
	res[0] = '0';
	tmp = size - 1;
	while (n > 0)
	{
		res[tmp--] = '0' + (n % 10);
		n /= 10;
	}
	res[size] = '\0';
	return (res);
}

static size_t	len(unsigned int n)
{
	size_t	res;

	res = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		res ++;
	}
	return (res);
}
