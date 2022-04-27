/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:52:48 by omanar            #+#    #+#             */
/*   Updated: 2022/04/27 05:17:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	get_next_line(char **buff)
{
	int		i;
	int		nobr;
	char	byte;
	char	*buffer;

	i = 0;
	nobr = 1;
	buffer = (char *)malloc(sizeof(char) * 10000);
	if (!buffer)
		return (-1);
	nobr = read(0, &byte, 1);
	while (nobr > 0 && byte != '\n' && byte != '\0')
	{
		if (byte != '\n' && byte != '\0')
			buffer[i] = byte;
		i++;
		nobr = read(0, &byte, 1);
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*buff = buffer;
	return (1);
}

void	here_doc(t_datab *data, char *limiter, char **av, char **env)
{
	char	*buff;

	if (pipe(data->end) == -1)
		error(NULL, errno);
	while (write(1, "here_doc>", 9) && get_next_line(&buff))
	{
		if (!ft_strncmp(buff, limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(buff, data->end[1]);
		free(buff);
	}
	free(buff);
	if (dup2(data->end[0], 0) == -1)
		error(NULL, errno);
	free(limiter);
	close(data->end[0]);
	close(data->end[1]);
	while (data->nofc <= data->last)
	{
		processing(data, av, env);
		data->nofc++;
	}
	while (wait(NULL) != -1)
		;
}

int	main(int ac, char **av, char **env)
{
	t_datab	data;

	if (ac < 5)
		error("Invalid arguments!\n", 1);
	if (!ft_strncmp(av[1], "here_doc", 9) && ac > 5)
	{
		parsing(&data, ac, av, 'h');
		here_doc(&data, ft_strjoin(av[2], "\n"), av, env);
	}
	else
	{
		parsing(&data, ac, av, 'p');
		pipex(&data, av, env);
	}
}
