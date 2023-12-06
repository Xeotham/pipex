/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/06 21:40:46 by mhaouas          ###   ########.fr       */
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

char	**get_flags(char *command, char *access)
{
	char	**flags;

	flags = ft_split(command, ' ');
	free(flags[0]);
	flags[0] = access;
	return (flags);
}
char	*test_access(char **exe_path, char *command)
{
    char    *tmp_path;
    char    **if_flags;

    if (!exe_path || !command || !*exe_path)
        return (NULL);
    if_flags = ft_split(command, ' ');
    if (!if_flags)
        return (NULL);
    if_flags[0] = free_and_join_after("/", if_flags[0]);
	if (!if_flags[0])
		return (NULL);
	tmp_path = check_access(exe_path, if_flags[0]);
    free(if_flags);
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