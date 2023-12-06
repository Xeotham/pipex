/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/04 15:37:11 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*creat_and_format_node(char	**func_path, char *command, int	cmd_number, int	number_of_commands)
{
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	node->command = test_access(func_path, command, node);
	if (!node->command)
	{
		free(node);
		return (NULL);
	}
	node->cmd_number = cmd_number + 1;
	node->total_number_of_cmd = number_of_commands;
	return (node);
}

t_pipex *create_link_list(char **func_path, char **commands, int number_of_commands)
{
	int	i;
	t_pipex	*first_node;
	t_pipex	*list;
	t_pipex	*next_node;

	i = 2;
	first_node = creat_and_format_node(func_path, commands[0], 0, number_of_commands);
	list = creat_and_format_node(func_path, commands[1], 1, number_of_commands);
	ft_pipe_lstadd_back(&first_node, list);
	if (!first_node || !list)
		return (NULL);
	next_node = list->next;
	while (i < number_of_commands)
	{
		next_node = creat_and_format_node(func_path, commands[i], i, number_of_commands);
		if (!next_node)
		{
			ft_pipe_lstclear(&first_node);
			return (NULL);
		}
		ft_pipe_lstadd_back(&list, next_node);
		list = list->next;
		next_node = next_node->next;
		i++;
	}
	return (first_node);
}