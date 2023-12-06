/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/06 22:04:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	when_child(int fd[2], t_pipex *pipe_struct, char **envp, int fd_out)
{
	int		new_fd[2];
	pid_t	pid;

	if (!pipe_struct)
	{
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		return ;
	}
	pipe(new_fd);
	close(fd[WRITE_FD]);
	close(new_fd[READ_FD]);
	dup2(fd[READ_FD], 0);
	dup2(new_fd[WRITE_FD], 1);
	if (pipe_struct->next)
	{
		ft_printf("%d", pipe_struct->cmd_number);
		pid = fork();
		if (pid == -1)
		{
			return ;		//error
		}
		else if (pid == 0)
			when_child(new_fd, pipe_struct->next, envp, fd_out);
		else
			execve(pipe_struct->command, pipe_struct->flags, envp);
	}
	else
	{
		dup2(new_fd[WRITE_FD], fd_out);
		execve(pipe_struct->command, pipe_struct->flags, envp);
	}
}

void	to_fork(int argc, char **argv, char **envp, t_pipex *pipe_struct)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	int		total_cmd;

	total_cmd = pipe_struct->total_number_of_cmd;
	fd_in = open(argv[0], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY, O_CREAT, O_TRUNC, 7770);
	pipe(pipe_fd);
		dup2(pipe_fd[WRITE_FD], fd_in);
		when_child(pipe_fd, pipe_struct->next, envp, fd_out);
}

int		main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipex		*pipe_struct;
	char		**func_path;

	i = 0;
	if (argc < 4)
		return (1);
	func_path = get_func_path(envp);
	pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	to_fork(argc, argv, envp, pipe_struct);
	/*while (pipe_struct)
	{
		ft_printf("%s\n%s\n", pipe_struct->command, pipe_struct->flags[1]);
		pipe_struct = pipe_struct->next;
	}*/
}
