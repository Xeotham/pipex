/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_fork_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:19:41 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/18 15:11:17 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_input_check(int fd_input[2], t_pipex *pipe_struct, int fd_type)
{
	if (fd_type == READ_FD && fd_input[READ_FD] == -1)
	{
		ft_pipe_lstclear(&pipe_struct);
		error_handler(FD_INPUT_ERROR);
	}
	else if (fd_type == WRITE_FD && fd_input[WRITE_FD] == -1)
	{
		close(fd_input[READ_FD]);
		ft_pipe_lstclear(&pipe_struct);
		error_handler(FD_OUTPUT_ERROR);
	}
	return ;
}

void	pipe_fd_check(int pipe_state, int fd_input[2], t_pipex *pipe_struct,
	char **envp)
{
	if (pipe_state == -1)
	{
		free_2d_array(envp);
		close_all_fd(fd_input);
		ft_pipe_lstclear(&pipe_struct);
		error_handler(PIPE_FAILED);
	}
	return ;
}

void	fork_check(int fd_input[2], int pipe_fd[2], t_pipex *pipe_struct,
	char **envp)
{
	free_2d_array(envp);
	close_all_fd(fd_input);
	close_all_fd(pipe_fd);
	ft_pipe_lstclear(&pipe_struct);
	error_handler(FORK_ERROR);
}
