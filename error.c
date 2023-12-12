/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:15:44 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/12 08:16:49 by mhaouas          ###   ########.fr       */
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
		error_message = "\033[31;1mERROR : Failed to input and/or output file.";
	write(2, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}
