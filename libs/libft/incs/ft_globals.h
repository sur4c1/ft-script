/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 06:23:21 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/25 05:57:13 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include "ft_types.h"

extern const t_fd	g_stdin;
extern const t_fd	g_stdout;
extern const t_fd	g_stderr;

extern int	g_argc;
extern char	**g_argv;
extern char	**g_envp;
