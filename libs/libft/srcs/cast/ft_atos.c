/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/08/26 16:51:04 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

short
ft_atos(const char *str)
{
	const char	  *current;
	short		   sign;
	unsigned short value;

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
		if (value > S16_MAX / 10
			|| (value == S16_MAX / 10
				&& *current - '0' > (S16_MAX % 10) + (1 - sign) / 2))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (sign * value);
}
