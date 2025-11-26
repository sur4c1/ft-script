/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bufdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 08:38:26 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/25 13:37:33 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_buff.h"

t_buff	ft_bufdup(t_buff src)
{
	t_buff	ret;

	ret.data = ft_memdup(src.data, src.len);
	ret.len = src.len;
	return (ret);
}
