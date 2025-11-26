/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atous.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:37:45 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/08/26 16:54:55 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"
#include "ft_def.h"
#include "ft_types.h"

unsigned short
ft_atous(const char *str)
{
	const char	  *current;
	unsigned short value;

	value = 0;
	current = str;
	while (ft_isspace(*current))
		current++;
	while (ft_isdigit(*current))
	{
		if (value > U16_MAX / 10
			|| (value == U16_MAX / 10 && (u16) *current - '0' > (U16_MAX % 10)))
			break;
		value *= 10;
		value += *current - '0';
		current++;
	}
	return (value);
}
