/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:01:25 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 18:02:06 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_array(char ***array)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *array;
	while (temp[++i])
		free(temp[i]);
	free(*array);
}

void	free_double(char ****array)
{
	int		i;
	char	***temp;

	i = -1;
	temp = *array;
	while (temp[++i])
	{
		free(temp[i][0]);
		free(temp[i][1]);
		free(temp[i]);
	}
	free(*array);
}

void	free_lex(t_lex *lex)
{
	t_lex	*temp;
	t_lex	*next;

	temp = lex;
	while (temp != NULL)
	{
		free(temp->token);
		free(temp->type);
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	free_join(t_shell *shell)
{
	if (shell->command)
	{
		free(shell->command);
		shell->command = NULL;
	}
	if (shell->flag)
	{
		free(shell->flag);
		shell->flag = NULL;
	}
	if (shell->content)
	{
		free(shell->content);
		shell->content = NULL;
	}
}

void	free_env(t_env *list)
{
	t_env	*temp;
	t_env	*next;

	temp = list;
	while (temp != NULL)
	{
		free(temp->variable);
		if (temp->value)
			free(temp->value);
		next = temp->next;
		free(temp);
		temp = next;
	}
}
