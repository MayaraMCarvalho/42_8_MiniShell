/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_void.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:29:13 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*remove_quotes_void(char *str)
{
	char	*line;
	int		i;
	int		k;
	int		empty;

	i = 0;
	k = 0;
	if (check_void(str, i))
		return (ft_strdup(str));
	line = (char *) malloc
		(ft_strlen(str) - (2 * quotes_void(str)) + 1 * sizeof(char));
	if (!line)
		return (NULL);
	while (str[i])
	{
		empty = 0;
		if (check_void(str, i) && i++)
			empty = 1;
		if (!empty)
			line[k++] = str[i];
		i++;
	}
	line[k] = '\0';
	return (line);
}

int	quotes_void(char *str)
{
	int		control;
	int		i;

	i = 0;
	control = 0;
	while (str[i] && control != 0)
	{
		if (check_void(str, i))
		{
			control++;
			i++;
		}
		i++;
	}
	return (control);
}

int	check_void(char *str, int i)
{
	if ((str[i] == '\'' && str[i + 1] && str[i + 1] == '\'')
		|| (str[i] == '"' && str[i + 1] && str[i + 1] == '"'))
		return (1);
	return (0);
}
