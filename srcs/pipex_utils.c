/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:21:18 by omanar            #+#    #+#             */
/*   Updated: 2022/04/27 05:42:19 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(char *str, int n)
{	
	if (!str)
		perror("Pipex");
	else
		ft_putstr_fd(str, 2);
	exit(n);
}

void	parsing(t_datab *data, int ac, char **av, char c)
{
	if (c == 'h')
	{
		data->nofc = 3;
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		data->infile = open(av[1], O_RDONLY);
		data->nofc = 2;
		data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	data->last = ac - 2;
}

void	child(t_datab *data, char **av, char **env)
{
	if (data->nofc == data->last)
	{
		if (data->outfile == -1)
			error(NULL, errno);
		if (dup2(data->outfile, 1) == -1)
			error(NULL, errno);
		close(data->outfile);
	}
	else
	{
		if (data->infile == -1 && data->nofc == 2)
			error("Pipex: no such file or directory\n", errno);
		if (dup2(data->end[1], 1) == -1)
			error(NULL, errno);
		close(data->infile);
	}
	close(data->end[0]);
	close(data->end[1]);
	run_command(data, av[data->nofc], env);
}

void	processing(t_datab *data, char **av, char **env)
{
	pid_t	pid;

	if (pipe(data->end) == -1)
		error(NULL, errno);
	pid = fork();
	if (pid == -1 && data->nofc < data->last)
		error(NULL, errno);
	if (pid == 0)
		child(data, av, env);
	else
	{
		if (dup2(data->end[0], 0) == -1)
			error(NULL, errno);
		close(data->end[0]);
		close(data->end[1]);
	}
}

void	pipex(t_datab *data, char **av, char **env)
{
	dup2(data->infile, 0);
	close(data->infile);
	while (data->nofc <= data->last)
	{
		processing(data, av, env);
		data->nofc++;
	}
	while (wait(NULL) != -1)
		;
}
