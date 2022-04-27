/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:37:51 by omanar            #+#    #+#             */
/*   Updated: 2021/11/19 00:06:52 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcnt(char const *s, char c)
{
	int	strs;

	strs = 0;
	while (*s)
	{
		if (*s != c)
		{
			strs++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (strs);
}

static void	ft_norm(char const **s, char c, int *last)
{
	while (**s && **s != c)
	{
		(*s)++;
		(*last)++;
	}
}

static void	free_handle(int i, char **split)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

static void	norminette(const char **s, char c, const char **str)
{
	while (**s && **s == c)
		(*s)++;
	*str = *s;
}

char	**ft_split(char const *s, char c)
{
	int			arr[2];
	char		**split;
	const char	*str;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_strcnt(s, c) + 1));
	if (!split)
		return (NULL);
	arr[0] = 0;
	while (*s)
	{
		arr[1] = 0;
		norminette(&s, c, &str);
		ft_norm(&s, c, &arr[1]);
		if (*(s - 1) != c)
			split[arr[0]++] = ft_substr(str, 0, arr[1]);
		if (arr[0] - 1 >= 0 && !split[arr[0] - 1])
		{
			free_handle(arr[0] - 2, split);
			return (NULL);
		}
	}
	split[arr[0]] = 0;
	return (split);
}
