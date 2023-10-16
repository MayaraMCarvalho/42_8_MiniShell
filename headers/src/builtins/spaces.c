/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:55:39 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	verify_spaceless(char	*token)
{
	int		i;
	int		control;

	i = -1;
	control = 0;
	if (!verify_list(token, ft_split("> < >> << |", ' ')))
	{
		while (token[++i])
		{
			if (token[i] == '|' || token[i] == '>' || token[i] == '<')
			{
				control++;
				if (token[i + 1] && (token[i] == '>' || token[i] == '<')
					&& token[i] == token[i + 1])
					i++;
			}
		}
	}
	return (control);
}

char	**create_spaces(char *token, int control)
{
	char	*spaces;
	char	**split;

	spaces = (char *) malloc
		((control * 2 + ft_strlen(token) + 1) * sizeof (char));
	if (!spaces)
		return (NULL);
	spaces = put_spaces(token, spaces);
	split = ft_split(spaces, ' ');
	free(spaces);
	return (split);
}

char	*put_spaces(char *token, char *spaces)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (token[++i])
	{
		if (token[i] == '|' || token[i] == '>' || token[i] == '<')
		{
			spaces[j++] = ' ';
			spaces[j++] = token[i];
			if (token[i + 1] && (token[i] == '>' || token[i] == '<')
				&& token[i] == token[i + 1])
				spaces[j++] = token[++i];
			spaces[j++] = ' ';
		}
		else
			spaces[j++] = token[i];
	}
	spaces[j] = '\0';
	return (spaces);
}
