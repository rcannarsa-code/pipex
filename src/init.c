/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:18 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/05 15:24:19 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv)
{
	pipex->cmd_count = argc - 3;
	pipex->here_doc = 0;
	pipex->limiter = NULL;
	pipex->pipe = NULL;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->pids = NULL;
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
		pipex->cmd_count--;
	}
	pipex->pipe = malloc(sizeof(int) * (2 * (pipex->cmd_count - 1)));
	pipex->cmd_paths = malloc(sizeof(char *) * (pipex->cmd_count + 1));
	pipex->cmd_args = malloc(sizeof(char **) * (pipex->cmd_count + 1));
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pipe || !pipex->cmd_paths || !pipex->cmd_args || !pipex->pids)
		error_exit("Memory allocation failed");
}
