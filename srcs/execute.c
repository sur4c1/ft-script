/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:03:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/11/26 15:45:48 by yyyyyy           ###   ########.fr       */
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
	if (logtype != 'H')
	{
		ft_putnbr_fd(diff.tv_sec, arguments->log_timing.fd);
		ft_putchar_fd('.', arguments->log_timing.fd);
		write_us(diff.tv_usec, arguments->log_timing.fd);
	}
	else
		ft_putstr_fd("0.000000", arguments->log_timing.fd);
	ft_putchar_fd(' ', arguments->log_timing.fd);
	switch (logtype)
	{
	case 'I':
	case 'O':
		ft_putnbr_fd(va_arg(ap, int), arguments->log_timing.fd);
		break;
	case 'H':
		ft_putstr_fd(va_arg(ap, char *), arguments->log_timing.fd);
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

int
execute(t_arguments arguments, char **envp)
{
	int			   master;
	int			   slave;
	int			   pid;
	struct pollfd  fd[2];
	int			   unlock_flag;
	char		   buffer[1024];
	usz			   byteread;
	struct termios termconfig;
	struct stat	   statbuf;
	int			   status;
	int			   pidstatus;

	status = 0;
	master = open("/dev/ptmx", O_RDWR | O_NOCTTY);
	if (master < 0)
		exit(1);
	unlock_flag = 0;
	ioctl(master, TIOCSPTLCK, &unlock_flag);
	slave = ioctl(master, TIOCGPTPEER, O_RDWR | O_NOCTTY);
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
			perror("child setup");
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
		perror("Execve");
		exit(42);
	}
	close(slave);
	fd[0] = (struct pollfd) {.fd = master, .events = POLLIN, .revents = 0};
	fd[1] = (struct pollfd) {.fd = 0, .events = POLLIN, .revents = 0};
	do
	{
		if (lastsig)
		{
			switch (lastsig)
			{
			case SIGUSR1:
				if (arguments.log_in.fd)
					fsync(arguments.log_in.fd);
				if (arguments.log_out.fd)
					fsync(arguments.log_out.fd);
				if (arguments.log_timing.fd)
					fsync(arguments.log_timing.fd);
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
				if (arguments.log_timing.fd
					&& arguments.logging_format == F_ADVANCED)
				{
					struct winsize w;

					ioctl(0, TIOCGWINSZ, &w);
					log_timing(&arguments, 'S', SIGWINCH, w.ws_row, w.ws_col);
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
		if (poll(fd, 2, 0))
		{
			if (arguments.flush)
			{
				fsync(arguments.log_in.fd);
				fsync(arguments.log_out.fd);
				fsync(arguments.log_timing.fd);
			}
			if (fd[0].revents & POLLIN)
			{
				byteread = read(master, buffer, sizeof(buffer));
				write(1, buffer, byteread);
				if (arguments.log_out.fd)
					write(arguments.log_out.fd, buffer, byteread);
				if (byteread && arguments.log_timing.fd)
					log_timing(&arguments, 'O', byteread);
			}
			if (fd[0].revents & POLLHUP)
				break;
			if (fd[1].revents & POLLIN)
			{
				byteread = read(0, buffer, sizeof(buffer));
				if (!byteread)
					write(master, "\004", 1);
				write(master, buffer, byteread);
				if (arguments.log_in.fd)
					write(arguments.log_in.fd, buffer, byteread);
				if (byteread && arguments.log_timing.fd)
					log_timing(&arguments, 'I', byteread);
			}
			fstat(arguments.log_in.fd, &statbuf);
			if (arguments.output_limit
				&& statbuf.st_size > arguments.output_limit)
				goto limit_exceeded;
			fstat(arguments.log_timing.fd, &statbuf);
			if (arguments.output_limit
				&& statbuf.st_size > arguments.output_limit)
				goto limit_exceeded;
			fstat(arguments.log_out.fd, &statbuf);
			if (arguments.output_limit
				&& statbuf.st_size > arguments.output_limit)
				goto limit_exceeded;
			continue;
		limit_exceeded:
			ft_putstr("Script terminated, max output files size ");
			ft_putnbr(arguments.output_limit);
			ft_putendl(" exceeded.");
			status |= 256;
			break;
		}
	} while (1);
	close(master);
	waitpid(pid, &pidstatus, 0);
	if (WIFEXITED(pidstatus))
		status |= WEXITSTATUS(pidstatus);
	if (WIFSIGNALED(pidstatus))
		status |= WSTOPSIG(pidstatus);
	return (status);
}
