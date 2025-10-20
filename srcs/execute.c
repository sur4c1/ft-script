/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:03:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/20 23:34:32 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include <poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int flusher;

void
execute(t_arguments arguments, char **envp)
{
	pid_t		  child;
	int			  in_pipe[2];
	int			  out_pipe[2];
	int			  status;
	struct pollfd fds[2];
	char		  buffer[1024];
	usz			  nbread;

	if (pipe(in_pipe) || pipe(out_pipe))
		exit(1);
	child = fork();
	if (child < 0)
		exit(1);
	if (!child)
	{
		setsid();
		dup2(out_pipe[1], STDOUT_FILENO);
		dup2(out_pipe[1], STDERR_FILENO);
		close(in_pipe[1]);
		close(out_pipe[0]);
		if (arguments.command[0])
			execve(arguments.shell,
				   (char *[]) {arguments.shell, "-c", arguments.command, NULL},
				   envp);
		else
			execve(arguments.shell, (char *[]) {arguments.shell, NULL}, envp);
		perror("execve");
		exit(42);
	}
	fds[0] = (struct pollfd) {STDIN_FILENO, POLLIN, 0};
	fds[1] = (struct pollfd) {out_pipe[0], POLLIN, 0};
	close(in_pipe[0]);
	close(out_pipe[1]);
	do
	{
		fds[0].revents = 0;
		fds[1].revents = 0;
		if (flusher)
		{
			fsync(arguments.log_out.fd);
			fsync(arguments.log_in.fd);
			fsync(arguments.log_timing.fd);
			flusher = 0;
		}
		nbread = poll(fds, 2, 0);
		if (nbread)
		{
			if (fds[1].revents & POLLIN)
			{
				nbread = read(out_pipe[0], buffer, sizeof(buffer));
				write(STDOUT_FILENO, buffer, nbread);
			}
			if (fds[0].revents & POLLIN)
			{
				nbread = read(STDIN_FILENO, buffer, sizeof(buffer));
				write(in_pipe[1], buffer, nbread);
				if (!nbread)
					close(in_pipe[1]);
			}
		}
	} while (!waitpid(child, &status, WNOHANG));
	close(in_pipe[1]);
	close(out_pipe[0]);
}
