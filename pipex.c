/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/04 15:05:36 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	to_fork(t_pipex *pipe_struct)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(FORK_ERROR);
	}
	else if (pid == 0)
	{
		//execute the child part (Need to refork and execve the command with flags)
	}
}*/

int		main(int argc, char **argv, char **envp)
{
	int			i;
	int			pipe_fd[2];
	t_pipex		*pipe_struct;
	char		**func_path;

	i = 0;
	if (argc < 4)
		return (1);
	pipe(pipe_fd);
	func_path = get_func_path(envp);
	pipe_struct = create_link_list(func_path, argv + 2, argc - 3);
	while (pipe_struct)
	{
		ft_printf("%s\n%s\n", pipe_struct->command, pipe_struct->flags);
		pipe_struct = pipe_struct->next;
	}
}
