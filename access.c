/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/04 15:54:35 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access(char **paths, char *cmd)
{
	int		i;
	char	*tmp_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], cmd);
		if (access(tmp_path, X_OK) == 0)
			break ; 
		free(tmp_path);
		i++;
	}
	if (access(tmp_path, X_OK) == -1)
		return (NULL);
	return (tmp_path);
}

char	*test_access(char **exe_path, char *command, t_pipex *pipe_struct)
{
    char    *tmp_cmd;
    char    *tmp_path;
    char    **if_flags;

    if (!exe_path || !command || !*exe_path)
        return (NULL);
    if_flags = ft_split(command, ' ');
    tmp_cmd = ft_strjoin("/", if_flags[0]);
    if (!tmp_cmd)
        return (NULL);
    pipe_struct->flags = ft_unsplit(if_flags + 1, " ");
    free(if_flags);
	tmp_path = check_access(exe_path, tmp_cmd);
    free(tmp_cmd);
    return (tmp_path);
}

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