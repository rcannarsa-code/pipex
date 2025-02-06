/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:13 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/05 15:45:07 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_process(t_pipex *pipex, int i, char **envp)
{
	int	j;

	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipe[1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->pipe[2 * i - 2], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipe[2 * i - 2], STDIN_FILENO);
		dup2(pipex->pipe[2 * i + 1], STDOUT_FILENO);
	}
	j = 0;
	while (j < (pipex->cmd_count - 1) * 2)
	{
		close(pipex->pipe[j]);
		j++;
	}
	close(pipex->infile);
	close(pipex->outfile);
	execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
	error_exit("Command execution failed");
}

void	execute_commands(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			error_exit("Pipe creation failed");
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] < 0)
			error_exit("Fork failed");
		if (pipex->pids[i] == 0)
			child_process(pipex, i, envp);
		i++;
	}
	i = 0;
	while (i < (pipex->cmd_count - 1) * 2)
	{
		close(pipex->pipe[i]);
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], NULL, 0);
		i++;
	}
}
