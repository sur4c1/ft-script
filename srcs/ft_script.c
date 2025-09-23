/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/09/23 17:56:06 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include "ft_script.h"
#include "define.h"
#include "libft.h"

#include <stdio.h>
void print_arguments(t_arguments arguments)
{
	printf("Arguments:\n");
	printf("  - log-in: %s\n", arguments.log_in.path);
	printf("  - log-out: %s\n", arguments.log_out.path);
	printf("  - log-io: %s\n", arguments.log_io.path);
	printf("  - log-timing: %s\n", arguments.log_timing.path);
	printf("  - logging-format: %s\n", (char *[]){"classic", "advanced"}[arguments.logging_format]);
	printf("  - append: %d\n", arguments.append);
	printf("  - return_exit_code: %d\n", arguments.return_exit_code);
	printf("  - flush: %d\n", arguments.flush);
	printf("  - follow-links: %d\n", arguments.follow_links);
	printf("  - quiet: %d\n", arguments.quiet);
	printf("  - echo: %s\n", (char *[]){"never", "always", "auto"}[arguments.echo]);
	printf("  - command: %s\n", arguments.command);
	printf("  - output-limit: %zu\n", arguments.output_limit);
}

int main(int argc, char **argv, char **envp)
{
	t_arguments arguments = {0};
	char shell[STR_SIZE];
	int status;

	status = parse_arguments(argc, argv, &arguments);
	print_arguments(arguments);
	// if (status)
	// 	return (status);
	// resolve_echo_flag(&arguments);
	// resolve_output_files(&arguments);
	// resolve_shell(shell, envp);
	// setup_signal_hooks();
	// if (!arguments.quiet)
	// 	ft_printf("Start\n");
	// status = execute(arguments);
	// if (!arguments.quiet)
	// 	ft_printf("End\n");
	// if (arguments.return_exit_code)
	// 	return (status);
	(void)shell;
	(void)envp;
	return (0);
}
