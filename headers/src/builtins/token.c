/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	***tokenization(t_shell *shell)
{
	char	*line;
	char	***lex;
	char	**token;
	t_lex	*lexer;

	line = remove_quotes_void(shell->line);
	token = ft_split_mod(line, ' ');
	free(line);
	verify_expansion(token);
	lexer = lexical(token);
	lex = make_lexer(lexer);
	if (!lex)
		return (NULL);
	free_array(&token);
	free_lex(lexer);
	return (lex);
}

int	lexer_size(t_lex *lexer)
{
	t_lex	*temp;
	t_lex	*next;
	int		i;

	temp = lexer;
	i = 0;
	while (temp != NULL)
	{
		i++;
		next = temp->next;
		temp = next;
	}
	return (i);
}

char	*id_token(char *token)
{
	if (token)
	{
		if (verify_exceptions(token))
			return (CONTENT);
		else if (verify_list(token,
				ft_split("echo cd pwd export unset env exit history", ' ')))
			return (BUILTIN);
		else if (token[0] == '-')
			return (FLAG);
		else
			return (CONTENT);
	}
	return (NULL);
}

void	copy_token(char **token, t_lex **lex)
{
	int		i;
	t_lex	*node;
	char	**spaces;
	int		control;

	i = -1;
	while (token[++i])
	{
		control = verify_spaceless(token[i]);
		if (control)
		{
			spaces = create_spaces(token[i], control);
			if (spaces)
			{
				copy_token(spaces, lex);
				free_array(&spaces);
			}
		}
		else
		{
			node = NULL;
			node = insert_front_lex(node, token[i], id_token(token[i]));
			insert_last_lex(lex, node);
		}
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
