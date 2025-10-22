/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:03:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/22 18:57:02 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include <asm/termbits.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int flusher;

void
execute(t_arguments arguments, char **envp)
{
	int			  master;
	int			  slave;
	int			  pid;
	struct pollfd fd[2];
	int			  unlock_flag;
	char		  buffer[1024];
	usz			  byteread;

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
		if (setsid() < 0 || ioctl(slave, TIOCSCTTY, 0) < 0
			|| dup2(slave, STDIN_FILENO) < 0 || dup2(slave, STDOUT_FILENO) < 0
			|| dup2(slave, STDERR_FILENO) < 0)
		{
			perror("child setup: ");
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
	do
	{
		fd[0] = (struct pollfd) {.fd = master, .events = POLLIN, .revents = 0};
		fd[1] = (struct pollfd) {.fd = 0, .events = POLLIN, .revents = 0};
		if (poll(fd, 2, -1))
		{
			if (fd[0].revents & POLLIN)
			{
				byteread = read(master, buffer, sizeof(buffer));
				if (!byteread)
					break;
				write(1, buffer, byteread);
				if (arguments.log_out.fd)
					write(arguments.log_out.fd, buffer, byteread);
			}
			if (fd[0].revents & POLLHUP)
				break;
			if (fd[1].revents & POLLIN)
			{
				byteread = read(0, buffer, sizeof(buffer));
				if (!byteread)
					break;
				write(master, buffer, byteread);
				if (arguments.log_in.fd)
					write(arguments.log_in.fd, buffer, byteread);
			}
		}
	} while (1);
	close(master);
}
