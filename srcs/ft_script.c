/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/12/08 15:41:32 by yyyyyy           ###   ########.fr       */
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
		ft_putstr_fd("\"", fd);
	}
	else
	{
		ft_putstr_fd("<not exectuted on a terminal>", fd);
	}
	ft_putendl_fd("]", fd);
}

static void
end_log(int fd, int status)
{
	struct timeval now;
	char		  *date;

	ft_putstr_fd("Script done on ", fd);
	gettimeofday(&now, NULL);
	date = ctime(&now.tv_sec);
	date[ft_strlen(date) - 1] = 0;
	ft_putstr_fd(date, fd);
	ft_putstr_fd(" [", fd);
	if (status & 256)
	{
		ft_putstr_fd("<max output size exceeded>", fd);
	}
	else
	{
		ft_putstr_fd("COMMAND_EXIT_CODE+\"", fd);
		ft_putnbr_fd(status & 255, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putendl_fd("]", fd);
}

static void
begin_advanced_log(int fd, char **envp, t_arguments arguments)
{
	struct timeval now;
	char		  *date;
	char		   str[STR_SIZE];
	struct winsize wsize;

	ft_putstr_fd("H 0.000000 START_TIME", fd);
	gettimeofday(&now, NULL);
	date = ctime(&now.tv_sec);
	ft_putstr_fd(date, fd);
	if (ioctl(0, TIOCGWINSZ, &wsize) != -1)
	{
		while (*envp)
		{
			if (ft_strnstr(*envp, "TERM=", 5) == *envp)
			{
				ft_putstr_fd("H 0.000000 TERM ", fd);
				ft_putstr_fd(*envp + 5, fd);
				ft_putchar_fd('\n', fd);
				break;
			}
			envp++;
		}
		ft_putstr_fd("H 0.000000 TTY ", fd);
		readlink("/dev/fd/0", str, STR_SIZE);
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		ft_putstr_fd("H 0.000000 COLUMNS ", fd);
		ft_putnbr_fd(wsize.ws_col, fd);
		ft_putstr_fd("\n", fd);
		ft_putstr_fd("H 0.000000 LINES ", fd);
		ft_putnbr_fd(wsize.ws_row, fd);
		ft_putstr_fd("\n", fd);
	}
	ft_putstr_fd("H 0.000000 SHELL ", fd);
	ft_putstr_fd(arguments.shell, fd);
	ft_putchar_fd('\n', fd);
	if (arguments.log_timing.fd)
	{
		ft_putstr_fd("H 0.000000 TIMING_LOG ", fd);
		ft_putstr_fd(arguments.log_timing.path, fd);
		ft_putchar_fd('\n', fd);
	}
	if (arguments.log_out.fd)
	{
		ft_putstr_fd("H 0.000000 OUTPUT_LOG ", fd);
		ft_putstr_fd(arguments.log_out.path, fd);
		ft_putchar_fd('\n', fd);
	}
	if (arguments.log_in.fd)
	{
		ft_putstr_fd("H 0.000000 INPUT_LOG ", fd);
		ft_putstr_fd(arguments.log_in.path, fd);
		ft_putchar_fd('\n', fd);
	}
}

static void
end_advanced_log(int fd, int status, t_arguments arguments)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	now.tv_sec -= arguments.begin.tv_sec;
	now.tv_usec -= arguments.begin.tv_usec;
	if (now.tv_usec < 0)
	{
		now.tv_sec -= 1;
		now.tv_usec += 1000 * 1000;
	}
	ft_putstr_fd("H 0.000000 DURATION ", fd);
	ft_putnbr_fd(now.tv_sec, fd);
	ft_putchar_fd('.', fd);
	write_us(now.tv_usec, fd);
	ft_putstr_fd("\nH 0.000000 EXIT_CODE ", fd);
	ft_putnbr_fd(status & 255, fd);
	ft_putchar_fd('\n', fd);
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
	if (arguments.log_timing.fd && arguments.logging_format == F_ADVANCED)
		begin_advanced_log(arguments.log_timing.fd, envp, arguments);
	status = execute(arguments, envp);
	if (arguments.log_in.fd)
		end_log(arguments.log_in.fd, status);
	if (arguments.log_out.fd && arguments.log_out.fd != arguments.log_in.fd)
		end_log(arguments.log_out.fd, status);
	if (arguments.log_timing.fd && arguments.logging_format == F_ADVANCED)
		end_advanced_log(arguments.log_timing.fd, status, arguments);
	ioctl(0, TCSETS, &base);
	if (!arguments.quiet)
		ft_putendl("Script done.");
	if (arguments.return_exit_code)
		return (status & 255);
	return (0);
}
