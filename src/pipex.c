/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:24 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/05 15:55:46 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		error_exit("Not enough arguments");
	}
	init_pipex(&pipex, argc, argv);
	parse_args(&pipex, argc, argv, envp);
	execute_commands(&pipex, envp);
	cleanup_pipex(&pipex);
	return (0);
}
