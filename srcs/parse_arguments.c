/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:15:24 by bguyot            #+#    #+#             */
/*   Updated: 2025/09/23 17:54:30 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "libft.h"
#include "t_arguments.h"

static void
print_help()
{
	ft_putstr(
		"Usage:\n"
		"script [options] [file]\n"
		"\n"
		"Make a typescript of a terminal session.\n"
		"\n"
		"Options:\n"
		"-I, --log-in <file>           log stdin to file\n"
		"-O, --log-out <file>          log stdout to file (default)\n"
		"-B, --log-io <file>           log stdin and stdout to file\n"
		"\n"
		"-T, --log-timing <file>       log timing information to file\n"
		"-t[<file>], --timing[=<file>] deprecated alias to -T (default file is "
		"stderr)\n"
		"-m, --logging-format <name>   force to 'classic' or 'advanced' "
		"format\n"
		"\n"
		"-a, --append                  append to the log file\n"
		"-c, --command <command>       run command rather than interactive "
		"shell\n"
		"-e, --return                  return exit code of the child process\n"
		"-f, --flush                   run flush after each write\n"
		"--force                   use output file even when it is a link\n"
		"-E, --echo <when>             echo input in session (auto, always or "
		"never)\n"
		"-o, --output-limit <size>     terminate if output files exceed size\n"
		"-q, --quiet                   be quiet\n"
		"\n"
		"-h, --help                    display this help\n"
		"-V, --version                 display version\n");
}

static void
print_version()
{
	ft_putstr("ft_script from ikar");
	ft_putendl(VERSION);
}

int parse_arguments(int argc, char **argv, t_arguments *arguments)
{
	int arg;
	const t_option options[] = {
		{"log-in", required_argument, NULL, 'I'},
		{"log-out", required_argument, NULL, 'O'},
		{"log-io", required_argument, NULL, 'B'},
		{"log-timing", required_argument, NULL, 'T'},
		{"timing", optional_argument, NULL, 't'},
		{"logging-format", required_argument, NULL, 'm'},
		{"append", no_argument, NULL, 'a'},
		{"command", required_argument, NULL, 'c'},
		{"return", no_argument, NULL, 'e'},
		{"flush", no_argument, NULL, 'f'},
		{"force", no_argument, NULL, 0xFF + 'F'},
		{"echo", required_argument, NULL, 'E'},
		{"output-limit", required_argument, NULL, 'o'},
		{"quiet", no_argument, NULL, 'q'},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'V'},
	};

	while ((arg = ft_getopt_long(argc, argv, "I:O:B:T:t::m:ac:efE:o:qhV",
								 options, NULL)) != -1)
	{
		switch (arg)
		{
		case 'I':
			arguments->log_in.path = ft_optarg;
			break;
		case 'O':
			arguments->log_out.path = ft_optarg;
			break;
		case 'B':
			arguments->log_io.path = ft_optarg;
			break;
		case 'T':
			arguments->log_timing.path = ft_optarg;
			break;
		case 't':
			if (ft_optarg)
				arguments->log_timing.path = ft_optarg;
			else
				arguments->log_timing.fd = STDERR_FILENO;
			break;
		case 'm':
			if (!ft_strcmp(ft_optarg, "classic"))
				arguments->logging_format = F_CLASSIC;
			else if (!ft_strcmp(ft_optarg, "advanced"))
				arguments->logging_format = F_ADVANCED;
			else
			{
				ft_putchar('\'');
				ft_putstr(ft_optarg);
				ft_putendl("' is not a valid logging format. Options are "
						   "'classic' and 'advanced'.");
				return (-1);
			}
			break;
		case 'a':
			arguments->append = true;
			break;
		case 'c':
			arguments->command = ft_optarg;
			break;
		case 'e':
			arguments->return_exit_code = true;
			break;
		case 'f':
			arguments->flush = true;
			break;
		case 0xFF + 'F':
			arguments->follow_links = true;
			break;
		case 'E':
			if (!ft_strcmp(ft_optarg, "never"))
				arguments->echo = E_NEVER;
			else if (!ft_strcmp(ft_optarg, "always"))
				arguments->echo = E_ALWAYS;
			else if (!ft_strcmp(ft_optarg, "auto"))
				arguments->echo = E_AUTO;
			else
			{
				ft_putchar('\'');
				ft_putstr(ft_optarg)
					ft_putendl("' is not a valid logging format. Options are "
							   "'never', 'always' and 'auto'.");
				return (-1);
			}
			break;
		case 'o':
			arguments->output_limit = ft_atoul(ft_optarg);
			break;
		case 'q':
			arguments->quiet = true;
		case 'h':
			print_help();
			exit(0);
		case 'V':
			print_version();
			exit(0);
		}
	}
	if (ft_optopt)
		return (-1);
	if (!arguments->log_out.path)
		arguments->log_out.path = ft_optarg;
	if (!arguments->log_out.path)
		arguments->log_out.path = "typescript";
	return (0);
}
