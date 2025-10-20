/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:03:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/20 18:01:05 by yyyyyy           ###   ########.fr       */
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

	child = fork();
	if (child < 0 || pipe(in_pipe) || pipe(out_pipe))
		exit(1);
	if (!child)
	{
		dup2(in_pipe[0], STDIN_FILENO);
		dup2(out_pipe[1], STDOUT_FILENO);
		// dup2(out_pipe[1], STDERR_FILENO);
		if (arguments.command[0])
			execve(arguments.shell,
				   (char *[]) {arguments.shell, "-c", arguments.command, NULL},
				   envp);
		else
			execve(arguments.shell, (char *[]) {arguments.shell, NULL}, envp);
		perror("execve");
		exit(0);
	}
	fds[0] = (struct pollfd) {STDIN_FILENO, POLLIN, 0};
	fds[1] = (struct pollfd) {out_pipe[0], POLLIN, 0};
	while (!waitpid(child, &status, WNOHANG))
	{
		if (flusher)
		{
			fsync(arguments.log_out.fd);
			fsync(arguments.log_in.fd);
			fsync(arguments.log_timing.fd);
			flusher = 0;
		}
		if (poll(fds, 2, 0))
		{
			if (fds[0].revents & POLLIN)
			{
				while ((nbread = read(STDIN_FILENO, buffer, sizeof(buffer)))
					   > 0)
					write(in_pipe[1], buffer, nbread);
			}
			if (fds[1].revents & POLLIN)
			{
				while ((nbread = read(out_pipe[0], buffer, sizeof(buffer))) > 0)
					write(STDOUT_FILENO, buffer, nbread);
			}
		}
	}
	if (WIFEXITED(status))
		ft_putnbr_fd(WEXITSTATUS(status), 2);
	else if (WIFSIGNALED(status))
		ft_putnbr_fd(WTERMSIG(status), 2);
	else
		ft_putstr_fd("AAAAAAAAAAAAAAA", 2);
}
