/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:07:29 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/21 12:21:37by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"

char *ft_optarg = NULL;
int ft_optind = 1;
int ft_optopt = 0;
t_bool ft_opterr = TRUE;

static t_bool is_option(str arg)
{
	return arg[0] == '-' && ft_strcmp(arg, "-");
}

static void swap_args(char *const argv[], int i, int j)
{
	char *tmp;

	tmp = argv[i];
	((char **)argv)[i] = argv[j];
	((char **)argv)[j] = tmp;
}

static void move_front(char *const argv[], int elemind, int nb_put_to_left)
{
	while (elemind > nb_put_to_left + 1)
	{
		swap_args(argv, elemind, elemind - 1);
		elemind--;
	}
}

static int shortparse(
	int argc,
	char *const argv[],
	const char *optstring,
	int *nextshrt)
{
	int optindex;
	int shrtindex;
	char *opt;

	optindex = ft_optind;
	shrtindex = (*nextshrt)++;
	if (!argv[optindex][*nextshrt])
	{
		ft_optind++;
		*nextshrt = 1;
	}
	opt = ft_strchr(optstring, argv[optindex][shrtindex]);
	if (!opt)
	{
		if (ft_opterr)
		{
			ft_putstr(argv[0]);
			ft_putstr(": invalid option -- ");
			ft_putchar(argv[optindex][shrtindex]);
			ft_putchar('\n');
		}
		ft_optopt = argv[optindex][shrtindex];
		return '?';
	}
	if (opt[1] == ':')
	{
		if (argv[optindex][shrtindex + 1])
		{
			ft_optarg = argv[optindex] + shrtindex + 1;
			ft_optind = optindex + 1;
		}
		else if (ft_optind < argc)
		{
			ft_optarg = argv[ft_optind];
			ft_optind = optindex + 2;
		}
		else if (opt[2] != ':')
		{
			if (ft_opterr)
			{
				ft_putstr(argv[0]);
				ft_putstr(": option requires an argument -- ");
				ft_putchar(argv[optindex][shrtindex]);
				ft_putchar('\n');
			}
			ft_optopt = argv[optindex][shrtindex];
			return '?';
		}
		*nextshrt = 1;
	}
	return argv[optindex][shrtindex];
}

static usz ft_optlen(str opt)
{
	usz i;

	i = 0;
	while (opt[i] && opt[i] != '=')
		i++;
	return i;
}

static const t_option *longparse(
	int argc,
	char *const argv[],
	const t_option *longopts,
	int *longindex)
{
	int i;
	char *opt;

	*longindex = -1;
	opt = argv[ft_optind++] + 2;
	i = 0;
	while (longopts[i].name)
	{
		if (!ft_strcmp(longopts[i].name, opt))
		{
			*longindex = i;
			break;
		}
		else if (!ft_strncmp(longopts[i].name, opt, ft_optlen(opt)))
		{
			if (*longindex != -1)
			{
				if (ft_opterr)
				{
					ft_putstr(argv[0]);
					ft_putstr(": option '--");
					ft_putstr(opt);
					ft_putstr("' is ambiguous\n");
				}
				*longindex = 0;
				return NULL;
			}
			*longindex = i;
		}
		i++;
	}
	if (*longindex == -1)
	{
		if (ft_opterr)
		{
			ft_putstr(argv[0]);
			ft_putstr(": unrecognized option '--");
			ft_putstr(opt);
			ft_putstr("'\n");
		}
		*longindex = 0;
		return NULL;
	}
	ft_optarg = ft_strchr(opt, '=');
	if (ft_optarg && longopts[*longindex].has_arg == no_argument && ft_opterr)
	{
		ft_putstr(argv[0]);
		ft_putstr(": option '--");
		ft_putstr(opt);
		ft_putstr("' doesn't allow an argument\n");
	}
	if (ft_optarg || longopts[*longindex].has_arg == no_argument)
	{
		if (ft_optarg)
			ft_optarg++;
		return longopts + *longindex;
	}
	if (ft_optind >= argc)
	{
		if (ft_opterr)
		{
			ft_putstr(argv[0]);
			ft_putstr(": option '--");
			ft_putstr(opt);
			ft_putstr("' requires an argument\n");
		}
		return longopts + *longindex;
	}
	ft_optarg = argv[ft_optind++];
	return longopts + *longindex;
}

int ft_getopt_long(
	int argc,
	char *const argv[],
	const char *optstring,
	const t_option *longopts,
	int *longindex)
{
	const t_option *longopt;
	static int nextshrt = 1;
	static int prevind = 0;
	static int nb_put_to_left = 0;

	ft_optarg = NULL;
	if (prevind)
		while (prevind < ft_optind)
			move_front(argv, prevind++, nb_put_to_left++);
	while (prevind < ft_optind)
		move_front(argv, prevind++, nb_put_to_left);
	while (ft_optind < argc && !is_option(argv[ft_optind]))
		ft_optind++;
	prevind = ft_optind;
	if (ft_optind >= argc)
	{
		ft_optind = nb_put_to_left + 1;
		return -1;
	}
	if (ft_strcmp(argv[ft_optind], "--") == 0)
	{
		move_front(argv, ft_optind, nb_put_to_left++);
		ft_optind = nb_put_to_left + 1;
		return -1;
	}
	if (longopts && ft_strncmp(argv[ft_optind], "--", 2) == 0)
	{
		longopt = longparse(argc, argv, longopts, longindex);
		if (longopt)
			return longopt->val;
		return '?';
	}
	return shortparse(argc, argv, optstring, &nextshrt);
}
