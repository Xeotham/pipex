/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:01:13 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 13:11:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_2d_array(char	**array)
{
	int	i;

	i = 0;
	
	while (array[i])
		free(array[i++]);
	free(array);
}

void	close_all_fd(int fd[2])
{
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
}

int		get_mirror_pipe(int pipe_needed)
{
	if (pipe_needed == PIPE_FD_1)
		return (PIPE_FD_2);
	else
		return (PIPE_FD_1);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*tmp;
	
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1)
		error_handler(MALLOC_ERROR);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}