/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:21 by omanar            #+#    #+#             */
/*   Updated: 2022/04/27 04:59:17 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_datab
{
	int		infile;
	int		outfile;
	int		nofc;
	int		last;
	int		end[2];
	char	**paths;
	char	**argv;
	char	*command;
}	t_datab;

void	error(char *str, int n);
void	parsing(t_datab *data, int ac, char **av, char c);
void	pipex(t_datab *data, char **av, char **env);
void	processing(t_datab *data, char **av, char **env);
void	child(t_datab *data, char **av, char **env);
void	run_command(t_datab *data, char *cmd, char **env);
char	**get_paths(char **env);
char	*get_cmd(char **paths, char *cmd);
void	free_paths(char **paths);
void	here_doc(t_datab *data, char *limiter, char **av, char **env);
int		get_next_line(char **buff);

#endif