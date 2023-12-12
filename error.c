/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:15:44 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/12 08:44:45 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(int error_case)
{
	char *error_message;

	if (error_case == ARGS_ERROR)
		error_message = "\033[31;1mERROR : Too much or too few arguments.";
	else if (error_case == FIND_PATH_ERROR)
		error_message = "\033[31;1mERROR : No 'PATH' environement variable.";
	else if (error_case == SPLIT_PATHE_ERROR)
		error_message = "\033[31;1mERROR : Error when spliting the 'PATH' environement variable.";
	else if (error_case == LLIST_FAIL)
		error_message = "\033[31;1mERROR : Failed to creat link list.";
	else if (error_case == SPLIT_ERROR)
		error_message = "\033[31;1mERROR : Failed to execute the ft_split() function.";
	else if (error_case == JOIN_ERROR)
		error_message = "\033[31;1mERROR : Failed to execute the ft_strjoin() function.";
	else if (error_case == FD_INPUT_ERROR)
		error_message = "\033[31;1mERROR : Failed to open input file.";
	else if (error_case == FD_OUTPUT_ERROR)
		error_message = "\033[31;1mERROR : Failed to open output file.";
	else if (error_case == PIPE_FAILED)
		error_message = "\033[31;1mERROR : Failed to make a pipe with the pipe() function.";
	else
		more_error_handler(error_case);
	write(2, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}

void	more_error_handler(int error_case)
{
	char	*error_message;

	if (error_case == FORK_ERROR)
		error_message = "\033[31;1mERROR : Failed to fork the code with the fork() function.";
	else if (error_case == DUP_ERROR)
		error_message = "\033[31;1mERROR : Failed to execute the dup2() function.";
	else if (error_case == EXECVE_ERROR)
		error_message = "\033[31;1mERROR : Failed to execute one of the input function.";
	write(2, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}
