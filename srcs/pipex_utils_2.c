/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:39:44 by omanar            #+#    #+#             */
/*   Updated: 2022/04/25 11:12:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				error("Pipex: split failed\n", 1);
			return (paths);
		}
		i++;
	}
	error("Pipex: path not found\n", 1);
	return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	run_command(t_datab *data, char *cmd, char **env)
{
	data->paths = get_paths(env);
	data->argv = ft_split(cmd, ' ');
	data->command = get_cmd(data->paths, data->argv[0]);
	if (!data->command)
	{
		free_paths(data->paths);
		error("Pipex: command not found\n", 127);
	}
	if (execve(data->command, data->argv, env) == -1)
		error(NULL, errno);
}
