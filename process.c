/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:40:57 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/12 08:36:19 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_input)
{
	if (dup2(fd_input, STDIN_FILENO) == -1)
		error_handler(DUP_ERROR);
	if (dup2(fds[WRITE_FD], STDOUT_FILENO) == -1)
		error_handler(DUP_ERROR);
	close(fds[READ_FD]);
	if (execve(pipe_struct->command, pipe_struct->flags, envp) == -1)
		error_handler(EXECVE_ERROR);
}

void	parent_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_output)
{
	if (dup2(fds[READ_FD], STDIN_FILENO) == -1)
		error_handler(DUP_ERROR);
	if (dup2(fd_output, STDOUT_FILENO) == -1)
		error_handler (DUP_ERROR);
	close(fds[WRITE_FD]);
	if (execve(pipe_struct->command, pipe_struct->flags, envp) == -1)
		error_handler(EXECVE_ERROR);
}
