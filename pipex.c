/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/11 18:05:56 by mhaouas          ###   ########.fr       */
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

void	pipex(char **argv, char **envp, t_pipex *pipe_struct)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		fd_input;
	int		fd_output;

	fd_input = open(argv[0], O_RDONLY);
	fd_output = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		child_process(pipe_fd, pipe_struct, envp, fd_input);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
			parent_process(pipe_fd, pipe_struct->next, envp, fd_output);
		else
		{
			wait(NULL);
			return ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	*pipe_struct;
	char	**func_path;

	i = 0;
	if (argc != 5)
		return (1);
	func_path = get_func_path(envp);
	pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	pipex(argv + 1, envp, pipe_struct);
	free_2d_array(func_path);
	ft_pipe_lstclear(&pipe_struct);
	return (0);
}
