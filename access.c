/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/01 18:09:11 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *test_access(char **exe_path, char *command, t_pipex *pipe_struct)
{
    int     i;
    char    *tmp_cmd;
    char    *tmp_path;
    char    **if_flags;

    i = 0;
    if (!exe_path || !command || !*exe_path)
        return (NULL);
    if_flags = ft_split(command, ' ');
    tmp_cmd = ft_strjoin("/", if_flags[0]);
    pipe_struct->flags = if_flags[1];
    free(if_flags);
    if (!tmp_cmd)
        return (NULL);
    while (exe_path[i])
    {
        tmp_path = ft_strjoin(exe_path[i], tmp_cmd);
        if (access(tmp_path, X_OK) == 0)
            break ;
        free(tmp_path);
        i++;
    }
    free(tmp_cmd);
    return (tmp_path);
}