/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:52 by omanar            #+#    #+#             */
/*   Updated: 2022/04/27 05:07:52 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_datab	data;

	if (ac != 5)
		error("Run it like this: \"./pipex infile cmd1 cmd2 outfile\"\n", 1);
	parsing(&data, ac, av, 'p');
	pipex(&data, av, env);
}
