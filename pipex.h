/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:46:04 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/01 18:02:41 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include "Libft/libft.h"

/* ======= struct =======*/
typedef struct s_pipex
{
    char    *command;
    char    *flags;
    int     r_fd;
    int     w_fd;
    void    *next;
} t_pipex ;


char    *test_access(char **ex_path, char *command, t_pipex *pipe_struct);

#endif