/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 18:07:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	***tokenization(t_shell *shell)
{
	char	***lex;
	char	**token;
	t_lex	*lexer;

	lexer = NULL;
	token = ft_split(shell->line, ' ');
	verify_expansion(token);
	copy_token(token, &lexer);
	lex = make_lexer(lexer);
	if (!lex)
		return (NULL);
	free_array(&token);
	free_lex(lexer);
	return (lex);
}

char	*id_token(char *token, int *has_content)
{
	if (token)
	{
		if (verify_list(token,
				ft_split("echo cd pwd export unset env exit history", ' ')))
			return (BUILTIN);
		else if (token[0] == '-' && !verify_flags(token, "n")
		&& *has_content == 0)
			return (FLAG);
		else
		{
			*has_content = 1;
			return (CONTENT);
		}
	}
	return (NULL);
}

void	copy_token(char **token, t_lex **lex)
{
	int		i;
	t_lex	*node;
	int		has_content;

	i = -1;
	has_content = 0;
	while (token[++i])
	{
		node = NULL;
		node = insert_front_lex(node, token[i], id_token(token[i],
				&has_content));
		insert_last_lex(lex, node);
	}
}

void	copy_list(char ***lex, t_lex *list, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		lex[i][0] = ft_strdup(list->token);
		lex[i][1] = ft_strdup(list->type);
		list = list->next;
	}
	lex[i] = NULL;
}
