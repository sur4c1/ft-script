/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:01 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/08/26 16:55:00 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

unsigned long
ft_atoul(const char *str)
{
	const char	 *current;
	unsigned long value;

	value = 0;
	current = str;
	while (ft_isspace(*current))
		current++;
	while (ft_isdigit(*current))
	{
		if (value > U64_MAX / 10
			|| (value == U64_MAX / 10 && (u64) *current - '0' > (U64_MAX % 10)))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (value);
}
