/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:20:50 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 13:12:13 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_new_line(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\n' && buff[i])
	{
		i++;
	}
	if (buff[i] == '\n')
		return (i + 1);
	return (-1);
}

char	*new_storage(char *storage)
{
	int		i;
	int		nb_to_line;
	char	*tmp;

	i = 0;
	if (!storage)
		return (NULL);
	nb_to_line = is_new_line(storage);
	if (nb_to_line < 0)
	{
		free(storage);
		return (NULL);
	}
	i = ft_strlen(storage + nb_to_line);
	if (i == 0)
	{
		free(storage);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp = ft_strcat("", storage + nb_to_line, tmp);
	free(storage);
	return (tmp);
}

char	*dup_to_new_line(char *storage)
{
	int		i;
	int		nb_to_line;
	char	*buffer;

	if (!storage)
		return (NULL);
	i = 0;
	if (is_new_line(storage) == -1)
		nb_to_line = ft_strlen(storage);
	else
		nb_to_line = is_new_line(storage);
	buffer = malloc(sizeof(char) * (nb_to_line + 1));
	if (!buffer)
		return (NULL);
	while (i < nb_to_line)
	{
		buffer[i] = storage[i];
		i++;
	}
	buffer[nb_to_line] = 0;
	return (buffer);
}

char	*gnl_loop(char *storage, int fd)
{
	char	*buffer;
	int		nb_char;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (1)
	{
		nb_char = read(fd, buffer, BUFFER_SIZE);
		if (nb_char == -1 || (nb_char == 0 && !storage))
		{
			free(buffer);
			return (NULL);
		}
		buffer[nb_char] = 0;
		storage = join_and_free(storage, buffer);
		if (is_new_line(storage) != -1 || nb_char < BUFFER_SIZE)
			break ;
	}
	free(buffer);
	return (storage);
}
