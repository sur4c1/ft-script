/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/10/11 00:15:07 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "define.h"
#include "t_arguments.h"
#include <signal.h>

static int flusher = 0;

static void
sighandler(int signal)
{
	flusher = 1;
	(void) signal;
}

int
main(int argc, char **argv, char **envp)
{
	t_arguments arguments = {0};
	int			status;

	status = parse_arguments(argc, argv, &arguments);
	if (status)
		return (status);
	if (!arguments.quiet)
		log_script_started(arguments);
	resolve_echo_flag(&arguments);
	status = open_log_files(&arguments);
	if (status)
		return (status);
	resolve_shell(&arguments, envp);
	signal(SIGUSR1, &sighandler);
	execute(arguments);
	if (!arguments.quiet)
		ft_putendl("End");
	return (0);
}
