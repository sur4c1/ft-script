/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:40:40 by bguyot            #+#    #+#             */
/*   Updated: 2025/11/25 15:00:01 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "t_arguments.h"

/**
 *	@brief Populate the arguments structure according to the arguments the user
 *		specified
 *	@param argc The number of arguments
 *	@param argv The array containing the values of the arguments
 *	@param arguments A pointer to the arguments structure to populate
 *	@return The appropriate error code
 */
int
parse_arguments(int argc, char **argv, t_arguments *arguments);

/**
 * @brief Log starting message to STDIN
 */
void
log_script_started(t_arguments arguments);

/**
 * @brief Resolve an echo flag set to AUTO
 */
void
resolve_echo_flag(t_arguments *arguments);

/**
 * @brief Open and create the log files
 */
int
open_log_files(t_arguments *arguments);

/**
 * @brief Resolve which shell to use, defaults to /bin/bash
 */
void
resolve_shell(t_arguments *s_arguments, char **envp);

/**
 * @brief Resolve wich logging format to use, and handle conflicts
 */
int
resolve_format(t_arguments *arguments);

/**
 * @brief Main loop
 */
int
execute(t_arguments arguments, char **envp);
