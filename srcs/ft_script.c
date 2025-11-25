/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/11/25 15:02:45 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "define.h"
#include "t_arguments.h"
#include <asm/termbits.h>
#include <signal.h>
#include <sys/ioctl.h>

int lastsig = 0;

static void
sighandler(int signal)
{
	lastsig = signal;
}

int
main(int argc, char **argv, char **envp)
{
	t_arguments	   arguments;
	int			   status;
	struct termios base;
	struct termios raw;

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
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGTSTP, &sighandler);
	signal(SIGWINCH, sighandler);
	signal(SIGTERM, sighandler);
	gettimeofday(&arguments.begin, NULL);
	gettimeofday(&arguments.lastlog, NULL);
	if (!arguments.quiet)
		log_script_started(arguments);
	ioctl(0, TCGETS, &base);
	raw = base;
	raw.c_lflag &= ~(ICANON | ECHO | ECHOCTL);
	ioctl(0, TCSETS, &raw);
	status = execute(arguments, envp);
	ioctl(0, TCSETS, &base);
	if (!arguments.quiet)
		ft_putendl("Script done.");
	if (arguments.return_exit_code)
		return (status);
	return (0);
}
