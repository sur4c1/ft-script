/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/10/29 16:50:16 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "define.h"
#include "t_arguments.h"
#include <signal.h>

int flusher = 0;

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
	resolve_echo_flag(&arguments);
	status = open_log_files(&arguments);
	if (status)
		return (status);
	status = resolve_format(&arguments);
	if (status)
		return (status);
	resolve_shell(&arguments, envp);
	signal(SIGUSR1, &sighandler);
	gettimeofday(&arguments.begin_time, NULL);
	if (!arguments.quiet)
		log_script_started(arguments);
	execute(arguments, envp);
	if (!arguments.quiet)
		ft_putendl("Script done.");
	return (0);
}
