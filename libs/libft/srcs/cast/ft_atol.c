/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:01 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/08/26 16:50:49 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

long
ft_atol(const char *str)
{
	const char	 *current;
	long		  sign;
	unsigned long value;

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
		if (value > S64_MAX / 10
			|| (value == S64_MAX / 10
				&& *current - '0' > (S64_MAX % 10) + (1 - sign) / 2))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (sign * value);
}
