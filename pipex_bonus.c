/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 13:11:50 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	next_process(int pipe_fd[2], int fd_input[2],
		t_pipex *pipe_struct, char **envp)
{
	if (pipe_struct->total_number_of_cmd == 2)
	{
		pipe_struct->pid = fork();
		if (pipe_struct->pid == -1)
			fork_check_man(fd_input, pipe_fd, pipe_struct, envp);
		else if (pipe_struct->pid == 0)
			process(pipe_fd, pipe_struct, envp, fd_input);
		else
		{
			wait(NULL);
			close_all_fd(pipe_fd);
			close_all_fd(fd_input);
			return ;
		}
	}
	else
		process_to_chain(pipe_fd, fd_input, pipe_struct, envp);
}

void	first_process(t_pipex *pipe_struct, int fd_input[2], char **envp)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		pipe_fd_check_man(-1, fd_input, pipe_struct, envp);
	pipe_struct->pid = fork();
	if (pipe_struct->pid == -1)
		fork_check_man(fd_input, pipe_fd, pipe_struct, envp);
	else if (pipe_struct->pid == 0)
		process(fd_input, pipe_struct, envp, pipe_fd);
	else
	{
		close(fd_input[READ_FD]);
		close(pipe_fd[WRITE_FD]);
		wait(NULL);
		next_process(pipe_fd, fd_input, pipe_struct->next, envp);
	}
}

void	pipex(int argc, char **argv, char **envp, t_pipex *pipe_struct)
{
	int		fd_input[2];

	fd_input[READ_FD] = open(argv[0], O_RDONLY);
	if (fd_input[READ_FD] == -1)
		fd_input_check(fd_input, pipe_struct, READ_FD);
	fd_input[WRITE_FD] = open(argv[argc - 1], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_input[WRITE_FD] == -1)
		fd_input_check(fd_input, pipe_struct, WRITE_FD);
	first_process(pipe_struct, fd_input, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipe_struct;
	char	**func_path;

	if (argc < 5)
		error_handler(ARGS_ERROR);
	func_path = get_func_path(envp);
	if (ft_strnstr(argv[1], "here_doc", 8))
		pipe_struct = create_link_list(func_path, argv + 3, argc - 4);
	else
		pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	free_2d_array(func_path);
	if (ft_strnstr(argv[1], "here_doc", 8))
		here_doc_setup(pipe_struct, argc - 1, argv + 1, envp);
	else
		pipex(argc - 1, argv + 1, envp, pipe_struct);
	ft_pipe_lstclear(&pipe_struct);
	return (0);
}
