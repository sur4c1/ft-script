/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:56:40 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/10/20 18:00:44 by yyyyyy           ###   ########.fr       */
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
		if (arguments->echo == E_AUTO)
		{
			if (ioctl(1, TIOCGWINSZ)
				== -1) // homemade isatty, somewhat less reliable, but man2 only
				arguments->echo = E_ALWAYS;
			else
				arguments->echo = E_NEVER;
		}
	}
}

int
open_log_files(t_arguments *arguments)
{
	if (arguments->log_in.path[0])
		arguments->log_in.fd
			= open(arguments->log_in.path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arguments->log_out.path[0])
		arguments->log_out.fd
			= open(arguments->log_out.path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arguments->log_timing.path[0])
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
