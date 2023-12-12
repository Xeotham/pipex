/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:46:04 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/12 08:15:34 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/*=========== LIBRARY ===========*/
# include "Libft/libft.h"
# include <sys/wait.h>

/*========= PIPE FD TYPE ========*/
# define READ_FD 0
# define WRITE_FD 1

/*========== ERROR CASE =========*/
# define ARGS_ERROR 0
# define FIND_PATH_ERROR 1
# define SPLIT_PATHE_ERROR 2
# define LLIST_FAIL 3
# define SPLIT_ERROR 4
# define JOIN_ERROR 5
# define FD_INPUT_ERROR 6

/*============ STRUCT ===========*/
typedef struct s_pipex
{
	char	*command;
	char	**flags;
	int		cmd_number;
	int		total_number_of_cmd;
	void	*next;
}			t_pipex;

/*========== PROTOTYPE ==========*/

/*test_access() is a function that check which path is needed to execute the linux command,*/
/*and return the command precede by the correct path to execute it.*/
char		*test_access(char **ex_path, char *command);
char		**get_func_path(char **envp);
t_pipex		*create_link_list(char **func_path, char **commands,
				int number_of_commands);
void		ft_pipe_lstclear(t_pipex **lst);
void		ft_pipe_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex		*ft_pipe_lstlast(t_pipex *lst);
char		*free_and_join_after(char *s1, char *s2);
char		**get_flags(char *command, char *access);
void		free_2d_array(char **array);
void		parent_process(int fds[2], t_pipex *pipe_struct, char **envp,
				int fd_output);
void		child_process(int fds[2], t_pipex *pipe_struct, char **envp,
				int fd_input);
void		error_handler(int error_case);

#endif