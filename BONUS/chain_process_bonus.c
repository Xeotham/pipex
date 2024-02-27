/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:47:45 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 13:12:33 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process_to_chain(int pipe_fd[2], int fd_input[2], t_pipex *pipe_struct,
	char **envp)
{
	int	all_fd[3][2];

	all_fd[FD_INPUT][READ_FD] = fd_input[READ_FD];
	all_fd[FD_INPUT][WRITE_FD] = fd_input[WRITE_FD];
	all_fd[PIPE_FD_1][READ_FD] = pipe_fd[READ_FD];
	all_fd[PIPE_FD_1][WRITE_FD] = pipe_fd[WRITE_FD];
	chain_process(all_fd, PIPE_FD_1, pipe_struct, envp);
}

void	is_equal(t_pipex *pipe_struct, int all_fd[3][2], int pipe_needed,
	char **envp)
{
	int	mirror_pipe;

	mirror_pipe = get_mirror_pipe(pipe_needed);
	if (pipe_struct->pid == 0)
	{
		close_all_fd(all_fd[mirror_pipe]);
		process(all_fd[pipe_needed], pipe_struct, envp, all_fd[FD_INPUT]);
	}
	else
	{
		close_all_fd(all_fd[FD_INPUT]);
		close_all_fd(all_fd[PIPE_FD_1]);
		close_all_fd(all_fd[PIPE_FD_2]);
		waitpid(pipe_struct->pid, NULL, 0);
	}
}

void	is_not_equal(t_pipex *pipe_struct, int all_fd[3][2], int pipe_needed,
	char **envp)
{
	int	mirror_pipe;

	mirror_pipe = get_mirror_pipe(pipe_needed);
	if (pipe_struct->pid == 0)
	{
		close(all_fd[FD_INPUT][WRITE_FD]);
		process(all_fd[pipe_needed], pipe_struct, envp, all_fd[mirror_pipe]);
	}
	else
	{
		close(all_fd[pipe_needed][READ_FD]);
		close(all_fd[mirror_pipe][WRITE_FD]);
		chain_process(all_fd, mirror_pipe, pipe_struct->next, envp);
		waitpid(pipe_struct->pid, NULL, 0);
	}
}

void	chain_process(int all_fd[3][2], int pipe_needed, t_pipex *pipe_struct,
		char **envp)
{
	int	mirror_pipe;

	mirror_pipe = get_mirror_pipe(pipe_needed);
	if (pipe(all_fd[mirror_pipe]) == -1)
	{
		close_all_fd(all_fd[FD_INPUT]);
		close_all_fd(all_fd[PIPE_FD_1]);
		free_2d_array(envp);
		error_handler(PIPE_FAILED);
	}
	pipe_struct->pid = fork();
	if (pipe_struct->pid == -1)
		fork_check_bonus(all_fd, pipe_struct, envp);
	if (pipe_struct->cmd_number < pipe_struct->total_number_of_cmd)
		is_not_equal(pipe_struct, all_fd, pipe_needed, envp);
	else if (pipe_struct->cmd_number == pipe_struct->total_number_of_cmd)
		is_equal(pipe_struct, all_fd, pipe_needed, envp);
}
