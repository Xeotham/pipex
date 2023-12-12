/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:01:13 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/11 18:52:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_and_join_after(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	free(s2);
	return (tmp);
}

void	free_2d_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
