/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:13 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/10 13:37:09 by rcannars         ###   ########.fr       */
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
	exit(127);
}

/* void	execute_commands(t_pipex *pipex, char **envp)
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
 */

 void	execute_commands(t_pipex *pipex, char **envp)
{
	int	i;
	int	status;

	// Creazione delle pipe
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			error_exit("Pipe creation failed");
		i++;
	}

	// Fork dei processi
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

	// Chiudere tutte le pipe nel processo padre
	i = 0;
	while (i < (pipex->cmd_count - 1) * 2)
		close(pipex->pipe[i++]);

	// Attendere i processi figli e gestire gli exit status
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0 && exit_status != 1) // Ignora exit status 1
				ft_printf("Command %d failed with status %d\n", i, exit_status);
		}
		i++;
	}
}
