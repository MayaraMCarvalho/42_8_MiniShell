/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:41:11 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_node(t_shell shell, t_lst *node, t_lst *new_node)
{
	if (node)
	{
		node->type = new_node->type;
		if (new_node->msg)
		{
			free(node->msg);
			node->msg = ft_strdup(new_node->msg);
		}
	}
	else
	{
		node = insert_front(node, new_node->var, new_node->msg, new_node->type);
		insert_last(&shell.env, node);
	}
}

t_lst	*get_min(t_lst *env)
{
	t_lst	*env_copy;
	t_lst	*node;

	if (env)
	{
		node = env;
		env_copy = env;
		while (env_copy != NULL)
		{
			if (env_copy->next
				&& (strcmp_order(node->var, env_copy->next->var)) > 0)
				node = env_copy->next;
			env_copy = env_copy->next;
		}
		return (node);
	}
	return (NULL);
}

t_lst	*remove_min(t_lst *list, char *var)
{
	t_lst	*temp;
	t_lst	*prev;

	temp = list;
	prev = NULL;
	while (temp != NULL && temp->var != var)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev == NULL)
		list = temp->next;
	else
		prev->next = temp->next;
	temp->next = NULL;
	temp->prev = NULL;
	return (list);
}
