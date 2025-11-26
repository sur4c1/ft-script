/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:00:33 by yyyyyy            #+#    #+#             */
/*   Updated: 2025/09/23 17:51:25 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_types.h"
#include "ft_printf.h"
#include "ft_string.h"
#include "ft_put.h"
#include <stdlib.h>

/**
 * @brief The global variable that is set to the next argument to be processed.
 */
extern char *ft_optarg;

/**
 * @brief The global variable that is set to the index of the next argument
 * 			to be processed.
 */
extern int ft_optind;

/**
 * @brief The global variable that is set to the option character that caused
 * 			an error.
 */
extern int ft_optopt;

/**
 * @brief The global variable that is set to FALSE if getopt() should not print
 * 			an error message.
 */
extern t_bool ft_opterr;

#undef no_argument
#undef required_argument
#undef optional_argument
typedef enum e_argtype
{
	no_argument = 0,
	required_argument = 1,
	optional_argument = 2
} t_argtype;

typedef struct s_option
{
	const char *name;
	t_argtype has_arg;
	int *flag;
	int val;
} t_option;

int ft_getopt_long(
	int argc,
	char *const argv[],
	const char *optstring,
	const t_option *longopts,
	int *longindex);
int ft_getopt(int argc, char *const argv[], const char *optstring);
int ft_getopt_long_only(
	int argc,
	char *const argv[],
	const char *optstring,
	const t_option *longopts,
	int *longindex);
