/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_long_only.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:54:45 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/21 09:56:10 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"

int		ft_getopt_long_only(
	int argc,
	char *const argv[],
	const char *optstring,
	const t_option *longopts,
	int *longindex
)
{
	return ft_getopt_long(argc, argv, "", longopts, longindex);
	(void) optstring;
}
