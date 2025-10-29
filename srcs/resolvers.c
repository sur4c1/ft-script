/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:56:40 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/29 16:50:40 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

void
resolve_echo_flag(t_arguments *arguments)
{
	if (arguments->echo == E_AUTO)
	{
		if (ioctl(1, TIOCGWINSZ) == -1)
			arguments->echo = E_ALWAYS;
		else
			arguments->echo = E_NEVER;
	}
}

int
resolve_format(t_arguments *arguments)
{
	int log_count;

	log_count = 0;
	if (arguments->log_out.path[0])
		log_count++;
	if (arguments->log_in.path[0])
		log_count++;
	if (arguments->logging_format == F_CLASSIC && log_count > 1
		&& arguments->log_timing.fd)
	{
		ft_putendl_fd(
			"ft_script: log multiple streams is mutually exclusive with "
			"'classic' format",
			STDERR_FILENO);
		return (1);
	}
	if (arguments->logging_format == F_AUTO)
		arguments->logging_format = log_count;
	return (0);
}

int
open_log_files(t_arguments *arguments)
{
	if (arguments->log_in.path[0])
		arguments->log_in.fd
			= open(arguments->log_in.path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!ft_strcmp(arguments->log_in.path, arguments->log_out.path))
		arguments->log_out.fd = arguments->log_in.fd;
	else if (arguments->log_out.path[0])
		arguments->log_out.fd
			= open(arguments->log_out.path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!ft_strcmp(arguments->log_timing.path, arguments->log_in.path))
		arguments->log_timing.fd = arguments->log_in.fd;
	else if (!ft_strcmp(arguments->log_timing.path, arguments->log_out.path))
		arguments->log_timing.fd = arguments->log_out.fd;
	else if (arguments->log_timing.path[0])
		arguments->log_timing.fd = open(arguments->log_timing.path,
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arguments->log_in.fd < 0 || arguments->log_out.fd < 0
		|| arguments->log_timing.fd < 0)
		return (ERROR);
	return (OK);
}

void
resolve_shell(t_arguments *arguments, char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "SHELL=", 6) == *envp)
		{
			ft_strlcpy(arguments->shell, *envp + 6, 1024);
			return;
		}
		envp++;
	}
	ft_strlcpy(arguments->shell, "/bin/bash", 1024);
}
