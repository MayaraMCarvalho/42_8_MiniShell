/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:56:13 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 18:07:34 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

char	***make_lexer(t_lex *list)
{
	char	***lex;
	int		size;

	size = lexer_size(list);
	lex = malloc_lexer(size);
	if (!lex)
		return (NULL);
	copy_list(lex, list, size);
	return (lex);
}

char	***malloc_lexer(int size)
{
	char	***lex;
	int		i;
	int		cols;

	i = 0;
	cols = 2;
	lex = (char ***) malloc ((size + 1) * sizeof(char **));
	if (!lex)
		return (NULL);
	while (i < size)
	{
		lex[i] = (char **) malloc (cols * sizeof(char *));
		if (!lex[i])
		{
			while (--i >= 0)
				free(lex[i]);
			free(lex);
			return (NULL);
		}
		i++;
	}
	return (lex);
}

t_lex	*insert_front_lex(t_lex *new, char *token, char *type)
{
	t_lex	*node;

	node = (t_lex *) malloc (sizeof (t_lex));
	if (!node)
		return (0);
	node->token = NULL;
	node->type = NULL;
	if (token)
		node->token = ft_strdup(token);
	if (type)
		node->type = ft_strdup(type);
	node->prev = NULL;
	node->next = new;
	if (new != NULL)
		new->prev = node;
	return (node);
}

void	insert_last_lex(t_lex **lst, t_lex *new)
{
	t_lex	*list;

	if (!lst)
		return ;
	if (*lst)
	{
		list = *lst;
		while (list->next != NULL)
			list = list->next;
		list->next = new;
		new->prev = list;
	}
	else
		*lst = new;
}
