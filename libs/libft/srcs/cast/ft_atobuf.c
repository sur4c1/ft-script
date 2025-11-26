/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atobuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:54:40 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/21 05:52:09 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cast.h"

t_buff	*ft_atobuf(char *str)
{
	t_buff	*ret;

	ret = ft_calloc(1, sizeof(t_buff));
	ret->data = ft_strdup(str);
	ret->len = ft_strlen(ret->data);
	return (ret);
}
