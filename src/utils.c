/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:28 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 15:42:35 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	cleanup_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->pipe)
		free(pipex->pipe);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->cmd_paths)
	{
		i = 0;
		while (pipex->cmd_paths[i])
			free(pipex->cmd_paths[i++]);
		free(pipex->cmd_paths);
	}
	if (pipex->cmd_args)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			free_array(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	close(pipex->infile);
	close(pipex->outfile);
}

void	handle_here_doc(t_pipex *pipex, char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		error_exit("Here_doc pipe failed");
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	pipex->infile = fd[0];
	close(fd[1]);
}
