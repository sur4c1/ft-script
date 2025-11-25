/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/11/25 17:32:41 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "define.h"
#include "t_arguments.h"
#include <asm/termbits.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

int lastsig = 0;

static void
sighandler(int signal)
{
	lastsig = signal;
}

static void
begin_log(int fd, char **envp)
{
	struct timeval now;
	char		  *date;
	char		   str[STR_SIZE];
	struct winsize wsize;

	ft_putstr_fd("Script started on ", fd);
	gettimeofday(&now, NULL);
	date = ctime(&now.tv_sec);
	date[ft_strlen(date) - 1] = 0;
	ft_putstr_fd(date, fd);
	ft_putstr_fd(" [", fd);
	if (ioctl(0, TIOCGWINSZ, &wsize) != -1)
	{
		while (*envp)
		{
			if (ft_strnstr(*envp, "TERM=", 5) == *envp)
			{
				ft_putstr_fd("TERM=\"", fd);
				ft_putstr_fd(*envp + 5, fd);
				ft_putstr_fd("\" ", fd);
				break;
			}
			envp++;
		}
		ft_putstr_fd("TTY=\"", fd);
		readlink("/dev/fd/0", str, STR_SIZE);
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\" ", fd);
		ft_putstr_fd("COLUMNS=\"", fd);
		ft_putnbr_fd(wsize.ws_col, fd);
		ft_putstr_fd("\" ", fd);
		ft_putstr_fd("LINES=\"", fd);
		ft_putnbr_fd(wsize.ws_row, fd);
		ft_putstr_fd("]", fd);
	}
	else
	{
		ft_putstr_fd("<not exectuted on a terminal>", fd);
	}
	ft_putendl_fd("]", fd);
	(void) envp;
}

static void
end_log(t_arguments arguments)
{
	(void) arguments;
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
	if (arguments.log_in.fd)
		begin_log(arguments.log_in.fd, envp);
	if (arguments.log_out.fd && arguments.log_out.fd != arguments.log_in.fd)
		begin_log(arguments.log_out.fd, envp);
	status = execute(arguments, envp);
	end_log(arguments);
	ioctl(0, TCSETS, &base);
	if (!arguments.quiet)
		ft_putendl("Script done.");
	if (arguments.return_exit_code)
		return (status);
	return (0);
}
