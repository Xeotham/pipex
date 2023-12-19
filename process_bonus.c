/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:40:57 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 13:11:42 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process(int fds_in[2], t_pipex *pipe_struct, char **envp,
		int fds_out[2])
{
	if (dup2(fds_in[READ_FD], STDIN_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds_in);
		close_all_fd(fds_out);
		error_handler(DUP_ERROR);
	}
	if (dup2(fds_out[WRITE_FD], STDOUT_FILENO) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds_in);
		close_all_fd(fds_out);
		error_handler(DUP_ERROR);
	}
	close_all_fd(fds_in);
	close_all_fd(fds_out);
	if (execve(pipe_struct->command, pipe_struct->flags, envp) == -1)
	{
		free_2d_array(envp);
		close_all_fd(fds_in);
		close_all_fd(fds_out);
		error_handler(EXECVE_ERROR);
	}
}
