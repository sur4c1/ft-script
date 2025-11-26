/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bufcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:01:53 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/25 13:39:04 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_buff.h"
#include <stdio.h>
#include <unistd.h>

t_buff	ft_bufcat(t_buff a, t_buff b)
{
	t_buff	ret;

	ret.data = malloc(a.len + b.len);
	if (!ret.data)
	{
		ret.len = 0;
		return (ret);
	}
	ft_memcpy(ret.data, a.data, a.len);
	ft_memcpy(ret.data + a.len, b.data, b.len);
	ret.len = a.len + b.len;
	return (ret);
}
