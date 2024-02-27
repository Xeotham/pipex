/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:40:57 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/15 16:06:42 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_input[2])
{
	if (dup2(fd_input[READ_FD], STDIN_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_input);
		error_handler(DUP_ERROR);
	}
	if (dup2(fds[WRITE_FD], STDOUT_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_input);
		error_handler(DUP_ERROR);
	}
	close_all_fd(fd_input);
	close_all_fd(fds);
	if (execve(pipe_struct->command, pipe_struct->flags, envp) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_input);
		error_handler(EXECVE_ERROR);
	}
}

void	parent_process(int fds[2], t_pipex *pipe_struct, char **envp,
		int fd_output[2])
{
	if (dup2(fds[READ_FD], STDIN_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_output);
		error_handler(DUP_ERROR);
	}
	if (dup2(fd_output[WRITE_FD], STDOUT_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_output);
		error_handler(DUP_ERROR);
	}
	close_all_fd(fd_output);
	close_all_fd(fds);
	if (execve(pipe_struct->command, pipe_struct->flags, envp) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds);
		close_all_fd(fd_output);
		error_handler(EXECVE_ERROR);
	}
}
