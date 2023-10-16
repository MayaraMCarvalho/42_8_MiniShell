/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:33 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*strchr_mod(const char *str, int c)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
				return ((char *)(str + 1));
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (NULL);
}

char	*strchr_rev(const char *str, int c)
{
	int			i;
	const char	*temp;

	i = 0;
	temp = str;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
				return ((char *)ft_substr(temp, 0, i));
			i++;
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (NULL);
}

int	isalnum_mod(char *c)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (c[++i] && r == 0)
	{
		if (!ft_isalnum(c[i]) && c[i] != '=' && c[i] != '_' && c[i] != '"')
			r = 1;
	}
	return (r);
}
