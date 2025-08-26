/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:18 by bguyot            #+#    #+#             */
/*   Updated: 2025/08/26 16:13:45 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_arguments.h"
#include "ft_script.h"
#include "define.h"
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	t_arguments arguments;
	char shell[STR_SIZE];
	int status;

	status = parse_arguments(argc, argv, &arguments);
	if (status)
		return (status);
	resolve_echo_flag(&arguments);
	resolve_output_files(&arguments);
	resolve_shell(shell, envp);
	setup_signal_hooks();
	if (!arguments.quiet)
		ft_printf("Start\n");
	status = execute(arguments);
	if (!arguments.quiet)
		ft_printf("End\n");
	if (arguments.return_exit_code)
		return (status);
	return (0);
}
