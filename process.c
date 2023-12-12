/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:40:57 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/11 18:55:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_input)
{
	dup2(fd_input, STDIN_FILENO);
	dup2(fds[WRITE_FD], STDOUT_FILENO);
	close(fds[READ_FD]);
	execve(pipe_struct->command, pipe_struct->flags, envp);
}

void	parent_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_output)
{
	dup2(fds[READ_FD], STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	close(fds[WRITE_FD]);
	execve(pipe_struct->command, pipe_struct->flags, envp);
}
