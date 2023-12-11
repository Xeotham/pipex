/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/11 17:43:24 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*creat_and_format_node(char **func_path, char *command, int cmd_number,
		int number_of_commands)
{
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	node->command = test_access(func_path, command);
	node->flags = get_flags(command, node->command);
	if (!node->command)
	{
		free(node);
		return (NULL);
	}
	node->cmd_number = cmd_number + 1;
	node->total_number_of_cmd = number_of_commands;
	node->next = NULL;
	return (node);
}

t_pipex	*create_link_list(char **func_path, char **commands,
		int number_of_commands)
{
	int i;
	t_pipex *first_node;
	t_pipex *second_node;

	i = 2;
	first_node = creat_and_format_node(func_path, commands[0], 0,
			number_of_commands);
	second_node = creat_and_format_node(func_path, commands[1], 1,
			number_of_commands);
	if (!first_node || !second_node)
		return (NULL);
	ft_pipe_lstadd_back(&first_node, second_node);
	return (first_node);
}