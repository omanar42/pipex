/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:43:12 by omanar            #+#    #+#             */
/*   Updated: 2021/11/18 21:37:13 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(unsigned int nb, int len)
{
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static void	*ft_loop(char *res, unsigned int nb, int len)
{
	while (nb > 0)
	{
		res[--len] = ((nb % 10) + '0');
		nb /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	nb;
	char			*res;

	len = 0;
	nb = n;
	if (n < 0)
	{
		len = 1;
		nb = -(unsigned int)n;
	}
	len = ft_intlen(nb, len);
	if (n == 0)
		len = 1;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	if (n == 0)
		res[0] = '0';
	res[len] = '\0';
	if (nb > 0)
		res = ft_loop(res, nb, len);
	if (n < 0)
		res[0] = '-';
	return (res);
}
