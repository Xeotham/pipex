/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/12 08:42:59 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	when_pid_isnt_zero(int pipe_fd[2], int fd_input[2],
		t_pipex *pipe_struct, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_handler(FORK_ERROR);
	else if (pid == 0)
		parent_process(pipe_fd, pipe_struct->next, envp, fd_input[WRITE_FD]);
	else
	{
		wait(NULL);
		close(pipe_fd[READ_FD]);
		close(pipe_fd[WRITE_FD]);
		close(fd_input[READ_FD]);
		close(fd_input[WRITE_FD]);
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
		error_handler(FD_INPUT_ERROR);
	fd_input[WRITE_FD] = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_input[WRITE_FD] == -1)
	{
		close(fd_input[READ_FD]);
		error_handler(FD_OUTPUT_ERROR);
	}
	if (pipe(pipe_fd) == -1)
		error_handler(PIPE_FAILED);
	pid = fork();
	if (pid == -1)
		error_handler(FORK_ERROR);
	else if (pid == 0)
		child_process(pipe_fd, pipe_struct, envp, fd_input[READ_FD]);
	else
		when_pid_isnt_zero(pipe_fd, fd_input, pipe_struct, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	*pipe_struct;
	char	**func_path;

	i = 0;
	if (argc != 5)
		error_handler(ARGS_ERROR);
	func_path = get_func_path(envp);
	pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	free_2d_array(func_path);
	pipex(argv + 1, envp, pipe_struct);
	ft_pipe_lstclear(&pipe_struct);
	return (0);
}
