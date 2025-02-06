/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:36 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/05 15:14:33 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
#include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "../libft/includes/ft_printf.h"


typedef struct s_pipex
{
    int     infile;
    int     outfile;
    int     *pipe;
    int     cmd_count;
    char    **cmd_paths;
    char    ***cmd_args;
    pid_t   *pids;
    int     here_doc;
    char    *limiter;
} t_pipex;

// Main functions
void    init_pipex(t_pipex *pipex, int argc, char **argv);
void    parse_args(t_pipex *pipex, int argc, char **argv, char **envp);
void    execute_commands(t_pipex *pipex, char **envp);
void    cleanup_pipex(t_pipex *pipex);

// Utils functions
char    *find_path(char *cmd, char **envp);
void    error_exit(char *msg);
void    handle_here_doc(t_pipex *pipex, char *limiter);
void    create_pipes(t_pipex *pipex);
void    free_array(char **arr);

#endif