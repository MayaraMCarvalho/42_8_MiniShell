/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:59:02 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	verify_quotes(const char *str)
{
	char	quote;
	int		i;

	i = 0;
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
	}
	return (i);
}

int	quotes_close(const char *str)
{
	int		control;
	char	quote;
	int		i;

	i = 0;
	control = -1;
	while (str[i] && control != 0)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			control = 0;
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				control++;
		}
		i++;
	}
	return (control);
}

void	clear_quotes(char **token, char *temp)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while ((*token) && (*token)[i])
	{
		if ((*token)[i] && ((*token)[i] == '\'' || (*token)[i] == '"'))
		{
			quote = (*token)[i];
			i++;
			while ((*token)[i] && (*token)[i] != quote)
				temp[j++] = (*token)[i++];
		}
		else
			temp[j++] = (*token)[i];
		i++;
	}
	temp[j] = '\0';
	free(*token);
	*token = temp;
}
