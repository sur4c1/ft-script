/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:21:21 by bguyot            #+#    #+#             */
/*   Updated: 2025/08/26 16:50:56 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

int
ft_atoi(const char *str)
{
	const char	*current;
	int			 sign;
	unsigned int value;

	value = 0;
	sign = 1;
	current = str;
	while (ft_isspace(*current))
		current++;
	while (*current == '+' || *current == '-')
	{
		if (*current == '-')
			sign *= -1;
		current++;
	}
	while (ft_isdigit(*current))
	{
		if (value > S32_MAX / 10
			|| (value == S32_MAX / 10
				&& *current - '0' > (S32_MAX % 10) + (1 - sign) / 2))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (sign * value);
}
