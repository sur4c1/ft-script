/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:45:03 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/25 05:57:47 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_globals.h"

const t_fd	g_stdin = 0;
const t_fd	g_stdout = 1;
const t_fd	g_stderr = 2;

int		g_argc;
char	**g_argv;
char	**g_envp;

__attribute__((constructor))
void	ft_init_globals(int argc, str argv[], str envp[])
{
	g_argc = argc;
	g_argv = argv;
	g_envp = envp;
}

__attribute__((destructor))
void	ft_free_globals(void)
{
	g_argc = 0;
	g_argv = NULL;
	g_envp = NULL;
}
