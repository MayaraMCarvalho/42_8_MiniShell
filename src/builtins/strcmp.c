/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:42:39 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	strcmp_mod(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	if (s1 && s2)
	{
		i = 0;
		len = ft_strlen(s1);
		if (len != ft_strlen(s2))
			return (1);
		while (i < len)
		{
			if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
			{
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
			}
			i++;
		}
		return (0);
	}
	return (1);
}

int	strcmp_order(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (0);
}

int	strcmp_rev(const char *s1, const char *s2)
{
	int	i;
	int	j;

	if (s1 && s2)
	{
		i = ft_strlen(s1) - 1;
		j = ft_strlen(s2) - 1;
		while (s1[i] && s2[j] && i > -1 && j > -1)
		{
			if (s1[i] != s2[j])
				return (1);
			i--;
			j--;
		}
		return (0);
	}
	return (1);
}
