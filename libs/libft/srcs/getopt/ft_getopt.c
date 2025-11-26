/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:53:00 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/21 09:55:38 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"

int		ft_getopt(int argc, char *const argv[], const char *optstring)
{
	return ft_getopt_long(argc, argv, optstring, NULL, NULL);
}
