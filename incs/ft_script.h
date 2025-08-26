/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguyot <bguyot@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:40:40 by bguyot            #+#    #+#             */
/*   Updated: 2025/08/25 18:02:21 by bguyot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	@brief Populate the arguments structure according to the arguments the user
 *		specified
 *	@param argc The number of arguments
 *	@param argv The array containing the values of the arguments
 *	@param arguments A pointer to the arguments structure to populate
 *	@return The appropriate error code
 */
int parse_arguments(int argc, char **argv, t_arguments *arguments);

/**
 *	@brief Set the echo flag of the correct mode, according to specified mode
 *		and tty context
 *	@param arguments A pointer to the arguments structure to modifiy 
 */
void resolve_echo_flag(t_arguments *arguments);

/**
 *	@brief Check the files specified in the structure and open() them
 *	@param arguments A pointer to the arguments structure to modifiy 
 */
void resolve_output_files(t_arguments *arguments);

/**
 *	@brief Set the shell field of the arguments structure according
 *		to the environnement, defaulting to bash
 *	@param arguments A pointer to the arguments structure to modifiy 
 */
void resolve_shell(char *shell, char **envp);

/**
 *	@brief Setup the signal hook for SIGUSR1 
 */
void setup_signal_hooks(void);

/**
 *	@brief Execute the shell and redirect the outputs inside the specified files
 *	@param arguments The arguments structure to use as a reference
 */
int execute(t_arguments arguments);
