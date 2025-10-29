/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arguments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:26:47 by bguyot            #+#    #+#             */
/*   Updated: 2025/10/29 16:19:00 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "libft.h"
#include <stdbool.h>
#include <sys/time.h>

typedef enum e_echo
{
	E_NEVER,
	E_ALWAYS,
	E_AUTO,
} t_echo;

typedef struct s_file
{
	int	 fd;
	char path[1024];
} t_file;

typedef enum e_format
{
	F_AUTO,
	F_CLASSIC,
	F_ADVANCED,
} t_format;

typedef struct s_arguments
{
	t_file		   log_in;
	t_file		   log_out;
	t_file		   log_timing;
	t_format	   logging_format;
	bool		   append;
	bool		   return_exit_code;
	bool		   flush;
	bool		   follow_links;
	bool		   quiet;
	char		   command[1024];
	char		   shell[1024];
	t_echo		   echo;
	usz			   output_limit;
	struct timeval begin_time;
} t_arguments;
