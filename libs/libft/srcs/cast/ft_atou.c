/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:21:21 by bguyot            #+#    #+#             */
/*   Updated: 2025/08/26 16:54:29 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

unsigned int
ft_atou(const char *str)
{
	const char	*current;
	unsigned int value;

	value = 0;
	current = str;
	while (ft_isspace(*current))
		current++;
	while (ft_isdigit(*current))
	{
		if (value > U32_MAX / 10
			|| (value == U32_MAX / 10 && (u32) *current - '0' > (U32_MAX % 1)))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (value);
}
