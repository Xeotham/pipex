/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:08 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/01 18:09:32 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **get_func_path(char **envp)
{
    int     i;
    char    **func_path;

    i = 0;
    while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
        i++;
    func_path = ft_split(envp[i] + 5, ':');
    return (func_path);
}
int main(int argc, char **argv, char **envp)
{
    int i;
    int         infile_fd;
    int         outfile_fd;
    t_pipex    *pipe_struct;
	char	    **func_path;

    i = 0;
    infile_fd = open(argv[1], O_RDWR);
    outfile_fd = open(argv[argc - 1], O_RDWR);
    pipe_struct = ft_calloc(sizeof(t_pipex), 1);
    if (infile_fd == -1 || outfile_fd == -1 || argc < 3)
        return (1);
    func_path = get_func_path(envp);
    pipe_struct->command = test_access(func_path, argv[2], pipe_struct);
    ft_printf("%s \n%s", pipe_struct->command, pipe_struct->flags);
}
