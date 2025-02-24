/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:21 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 15:42:34 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (ft_strdup(cmd));
	paths = ft_split(*envp + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
	}
	free_array(paths);
	return (ft_strdup(cmd));
}

void	handle_files(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->here_doc)
	{
		handle_here_doc(pipex, pipex->limiter);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			ft_putstr_fd("Input file error\n", 2);
			argv[1] = NULL;
			argv[2] = "echo -n";
		}
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	if (pipex->outfile < 0)
	{
		error_exit("Output file error");
		exit(1);
	}
}

void	process_command(t_pipex *pipex, char **argv, char **envp, int index)
{
	int	start;

	if (pipex->here_doc)
		start = 3;
	else
		start = 2;
	pipex->cmd_args[index] = ft_split(argv[index + start], ' ');
	if (!pipex->cmd_args[index] || !pipex->cmd_args[index][0])
	{
		ft_putstr_fd("Empty command\n", 2);
		exit(1);
	}
	pipex->cmd_paths[index] = get_cmd_path(pipex->cmd_args[index][0], envp);
}

void	parse_args(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	handle_files(pipex, argc, argv);
	i = 0;
	while (i < pipex->cmd_count)
	{
		process_command(pipex, argv, envp, i);
		i++;
	}
	pipex->cmd_args[i] = NULL;
	pipex->cmd_paths[i] = NULL;
}
/* void	parse_args(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;
	int	start;

	i = 0;
	if (pipex->here_doc)
		start = 3;
	else
		start = 2;
	if (pipex->here_doc)
		handle_here_doc(pipex, pipex->limiter);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			ft_putstr_fd("Input file error\n", 2);
			argv[1] = NULL;
			argv[2] = "echo -n";
		}
	}
	if (pipex->here_doc)
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (pipex->outfile < 0)
	{
		error_exit("Output file error");
		exit(1);
	}
	while (i < pipex->cmd_count)
	{
		pipex->cmd_args[i] = ft_split(argv[i + start], ' ');
		if (!pipex->cmd_args[i] || !pipex->cmd_args[i][0])
		{
			ft_putstr_fd("Empty command\n", 2);
			exit(1);
		}
		pipex->cmd_paths[i] = get_cmd_path(pipex->cmd_args[i][0], envp);
		i++;
	}
	pipex->cmd_args[i] = NULL;
	pipex->cmd_paths[i] = NULL;
} */
