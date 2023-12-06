/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:46:04 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/04 15:36:26 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include "Libft/libft.h"

# define FORK_ERROR 1
/* ======= struct =======*/
typedef struct s_pipex
{
    char    *command;
    char    *flags;
    int     r_fd;
    int     w_fd;
	int		cmd_number;
	int		total_number_of_cmd;
    void    *next;
} t_pipex ;


char	*test_access(char **ex_path, char *command, t_pipex *pipe_struct);
char    **get_func_path(char **envp);
t_pipex *create_link_list(char **func_path, char **commands, int number_of_commands);
void	ft_pipe_lstclear(t_pipex **lst);
void	ft_pipe_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex	*ft_pipe_lstlast(t_pipex *lst);


#endif