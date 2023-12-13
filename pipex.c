/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/13 16:03:42 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	when_pid_isnt_zero(int pipe_fd[2], int fd_input[2],
		t_pipex *pipe_struct, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_check(fd_input, pipe_fd, pipe_struct, envp);
	else if (pid == 0)
		parent_process(pipe_fd, pipe_struct->next, envp, fd_input[WRITE_FD]);
	else
	{
		wait(NULL);
		close_all_fd(pipe_fd);
		close_all_fd(fd_input);
		return ;
	}
}

void	pipex(char **argv, char **envp, t_pipex *pipe_struct)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		fd_input[2];

	fd_input[READ_FD] = open(argv[0], O_RDONLY);
	if (fd_input[READ_FD] == -1)
		fd_input_check(fd_input, pipe_struct, READ_FD);
	fd_input[WRITE_FD] = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_input[WRITE_FD] == -1)
		fd_input_check(fd_input, pipe_struct, WRITE_FD);
	if (pipe(pipe_fd) == -1)
		pipe_fd_check(-1, fd_input, pipe_struct, envp);
	pid = fork();
	if (pid == -1)
		fork_check(fd_input, pipe_fd, pipe_struct, envp);
	else if (pid == 0)
		child_process(pipe_fd, pipe_struct, envp, fd_input[READ_FD]);
	else
		when_pid_isnt_zero(pipe_fd, fd_input, pipe_struct, envp);
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
