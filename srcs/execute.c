/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:03:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/12/11 15:29:02 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include <asm/termbits.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int lastsig;

void
write_us(long nb, int fd)
{
	ft_putnbr_fd(nb / 100000, fd);
	ft_putnbr_fd(nb % 100000 / 10000, fd);
	ft_putnbr_fd(nb % 10000 / 1000, fd);
	ft_putnbr_fd(nb % 1000 / 100, fd);
	ft_putnbr_fd(nb % 100 / 10, fd);
	ft_putnbr_fd(nb % 10, fd);
}

static void
log_timing(t_arguments *arguments, int logtype, ...)
{
	struct timeval now;
	struct timeval diff;
	va_list		   ap;

	va_start(ap, logtype);
	gettimeofday(&now, NULL);
	diff.tv_sec = now.tv_sec - arguments->lastlog.tv_sec;
	diff.tv_usec = now.tv_usec - arguments->lastlog.tv_usec;
	while (diff.tv_usec < 0)
	{
		diff.tv_usec += 1000 * 1000;
		diff.tv_sec -= 1;
	}
	if (arguments->logging_format == F_ADVANCED)
	{
		write(arguments->log_timing.fd, &logtype, 1);
		write(arguments->log_timing.fd, " ", 1);
	}
	ft_putnbr_fd(diff.tv_sec, arguments->log_timing.fd);
	ft_putchar_fd('.', arguments->log_timing.fd);
	write_us(diff.tv_usec, arguments->log_timing.fd);
	ft_putchar_fd(' ', arguments->log_timing.fd);
	switch (logtype)
	{
	case 'I':
	case 'O':
		ft_putnbr_fd(va_arg(ap, int), arguments->log_timing.fd);
		break;
	case 'S':
		switch (va_arg(ap, int))
		{
		case SIGWINCH:
			ft_putstr_fd("SIGWINCH ROWS=", arguments->log_timing.fd);
			ft_putnbr_fd(va_arg(ap, int), arguments->log_timing.fd);
			ft_putstr_fd(" COLS=", arguments->log_timing.fd);
			ft_putnbr_fd(va_arg(ap, int), arguments->log_timing.fd);
			break;
		case SIGTERM:
			ft_putstr_fd("SIGTERM", arguments->log_timing.fd);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	ft_putchar_fd('\n', arguments->log_timing.fd);
	arguments->lastlog = now;
	va_end(ap);
}

static int
watch_io(struct pollfd fd[2], t_arguments arguments)
{
	usz	 byte;
	char buf[1024];

	if (!poll(fd, 2, 0))
		return 0;
	if (fd[0].revents & POLLIN)
	{
		byte = read(fd[0].fd, buf, sizeof(buf));
		if (!byte)
			return 1;
		write(1, buf, byte);
		if (arguments.log_out.fd)
			write(arguments.log_out.fd, buf, byte);
		if (arguments.log_timing.fd)
			log_timing(&arguments, 'O', byte);
	}
	else if (fd[1].revents & POLLIN)
	{
		byte = read(fd[1].fd, buf, sizeof(buf));
		if (!byte)
		{
			write(fd[0].fd, "\004", 1);
			return 0;
		}
		write(fd[0].fd, buf, byte);
		if (arguments.log_in.fd)
			write(arguments.log_in.fd, buf, byte);
		if (arguments.log_timing.fd)
			log_timing(&arguments, 'I', byte);
	}
	else if (fd[0].revents & POLLHUP)
		return 1;
	else if (fd[1].revents & POLLHUP)
		write(fd[0].fd, "\004", 1);
	return 0;
}

static void
flush_all(t_arguments arguments)
{
	if (arguments.log_in.fd)
		fsync(arguments.log_in.fd);
	if (arguments.log_out.fd)
		fsync(arguments.log_out.fd);
	if (arguments.log_timing.fd)
		fsync(arguments.log_timing.fd);
}

static void
watch_signals(t_arguments arguments, int master, int slave,
			  struct winsize wsize)
{
	if (lastsig)
	{
		switch (lastsig)
		{
		case SIGUSR1:
			flush_all(arguments);
			break;
		case SIGINT:
			write(master, "\003", 1);
			break;
		case SIGQUIT:
			write(master, "\034", 1);
			break;
		case SIGTSTP:
			write(master, "\032", 1);
			break;
		case SIGWINCH:
			ioctl(0, TIOCGWINSZ, &wsize);
			ioctl(slave, TIOCSWINSZ, &wsize);
			if (arguments.log_timing.fd
				&& arguments.logging_format == F_ADVANCED)
			{
				log_timing(&arguments, 'S', SIGWINCH, wsize.ws_row,
						   wsize.ws_col);
			}
			break;
		case SIGTERM:
			if (arguments.log_timing.fd
				&& arguments.logging_format == F_ADVANCED)
			{
				log_timing(&arguments, 'S', SIGTERM);
			}
		default:;
		}
		lastsig = 0;
	}
}

int
execute(t_arguments arguments, char **envp)
{
	int			   master;
	int			   slave;
	int			   pid;
	struct pollfd  fd[2];
	int			   unlock_flag;
	struct termios termconfig;
	struct stat	   statbuf;
	int			   status;
	int			   pid_status;
	struct winsize wsize;

	int			   log = open("log", O_APPEND | O_WRONLY);
	status = 0;
	master = open("/dev/ptmx", O_RDWR | O_NOCTTY);
	if (master < 0)
		exit(1);
	unlock_flag = 0;
	ioctl(master, TIOCSPTLCK, &unlock_flag);
	slave = ioctl(master, TIOCGPTPEER, O_RDWR | O_NOCTTY);
	ioctl(0, TIOCGWINSZ, &wsize);
	ioctl(slave, TIOCSWINSZ, &wsize);
	if (slave < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
	{
		if (arguments.echo == E_NEVER)
		{
			ioctl(slave, TCGETS, &termconfig);
			termconfig.c_lflag &= ~(ECHO);
			ioctl(slave, TCSETS, &termconfig);
		}
		if (setsid() < 0 || ioctl(slave, TIOCSCTTY, 0) < 0
			|| dup2(slave, STDIN_FILENO) < 0 || dup2(slave, STDOUT_FILENO) < 0
			|| dup2(slave, STDERR_FILENO) < 0)
		{
			exit(1);
		}
		close(slave);
		close(master);
		if (arguments.command[0])
			execve(arguments.shell,
				   (char *[]) {arguments.shell, "-c", arguments.command, NULL},
				   envp);
		else
			execve(arguments.shell, (char *[]) {arguments.shell, NULL}, envp);
		exit(42);
	}
	fd[0] = (struct pollfd) {.fd = master, .events = POLLIN, .revents = 0};
	fd[1] = (struct pollfd) {.fd = 0, .events = POLLIN, .revents = 0};
	do
	{
		if (watch_io(fd, arguments))
			break;
		if (arguments.flush)
			flush_all(arguments);
		watch_signals(arguments, master, slave, wsize);
		fstat(arguments.log_in.fd, &statbuf);
		if (arguments.output_limit && statbuf.st_size > arguments.output_limit)
			goto limit_exceeded;
		fstat(arguments.log_timing.fd, &statbuf);
		if (arguments.output_limit && statbuf.st_size > arguments.output_limit)
			goto limit_exceeded;
		fstat(arguments.log_out.fd, &statbuf);
		if (arguments.output_limit && statbuf.st_size > arguments.output_limit)
			goto limit_exceeded;
		else if (waitpid(pid, &pid_status, WNOHANG))
			break;
		continue;
	limit_exceeded:
		ft_putstr("Script terminated, max output files size ");
		ft_putnbr(arguments.output_limit);
		ft_putendl(" exceeded.");
		status |= 256;
		break;
	} while (1);
	close(slave);
	close(master);
	waitpid(pid, &pid_status, 0);
	if (WIFEXITED(pid_status))
		status |= WEXITSTATUS(pid_status);
	if (WIFSIGNALED(pid_status))
		status |= WSTOPSIG(pid_status);
	ft_putendl_fd("end\n", log);
	close(log);
	return (status);
}
