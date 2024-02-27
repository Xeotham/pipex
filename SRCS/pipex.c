/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/20 14:15:14 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	when_pid_isnt_zero(int pipe_fd[2], int fd_input[2],
		t_pipex *pipe_struct, char **envp)
{
	pipe_struct->pid = fork();
	if (pipe_struct->pid == -1)
		fork_check(fd_input, pipe_fd, pipe_struct, envp);
	else if (pipe_struct->pid == 0)
		parent_process(pipe_fd, pipe_struct->next, envp, fd_input);
	else
	{
		close_all_fd(pipe_fd);
		close_all_fd(fd_input);
		waitpid(pipe_struct->pid, NULL, 0);
		return ;
	}
}

void	pipex(char **argv, char **envp, t_pipex *pipe_struct)
{
	int		pipe_fd[2];
	int		fd_input[2];

	fd_input[READ_FD] = open(argv[0], O_RDONLY);
	if (fd_input[READ_FD] == -1)
		fd_input_check(fd_input, pipe_struct, READ_FD);
	fd_input[WRITE_FD] = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_input[WRITE_FD] == -1)
		fd_input_check(fd_input, pipe_struct, WRITE_FD);
	if (pipe(pipe_fd) == -1)
		pipe_fd_check(-1, fd_input, pipe_struct, envp);
	pipe_struct->pid = fork();
	if (pipe_struct->pid == -1)
		fork_check(fd_input, pipe_fd, pipe_struct, envp);
	else if (pipe_struct->pid == 0)
		child_process(pipe_fd, pipe_struct, envp, fd_input);
	else
	{
		close(fd_input[READ_FD]);
		close(pipe_fd[WRITE_FD]);
		when_pid_isnt_zero(pipe_fd, fd_input, pipe_struct, envp);
		waitpid(pipe_struct->pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipe_struct;
	char	**func_path;

	if (argc != 5)
		error_handler(ARGS_ERROR);
	func_path = get_func_path(envp);
	pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	free_2d_array(func_path);
	pipex(argv + 1, envp, pipe_struct);
	ft_pipe_lstclear(&pipe_struct);
	return (0);
}
