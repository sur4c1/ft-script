/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:55:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/11 00:16:30 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"

void
log_script_started(t_arguments arguments)
{
	ft_putstr("Script started");
	if (arguments.log_out.path)
	{
		ft_putstr(", output log file is '");
		ft_putstr(arguments.log_out.path);
		ft_putchar('\'');
	}
	if (arguments.log_in.path)
	{
		ft_putstr(", input log file is '");
		ft_putstr(arguments.log_in.path);
		ft_putchar('\'');
	}
	if (arguments.log_timing.path)
	{
		ft_putstr(", timing file is '");
		ft_putstr(arguments.log_timing.path);
		ft_putchar('\'');
	}
	ft_putendl(".");
}
