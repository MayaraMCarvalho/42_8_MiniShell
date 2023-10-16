/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:29:48 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*tranfer_env(t_lst *env)
{
	t_env	*new;
	t_env	*node;
	char	*var;
	char	*value;
	int		type;

	new = NULL;
	while (env)
	{
		var = ft_strdup(env->var);
		value = ft_strdup(env->msg);
		if (env->type)
			type = env->type;
		else
			type = ENVP;
		node = NULL;
		node = insert_front_env(node, var, value, type);
		free(var);
		free(value);
		insert_last_env(&new, node);
		env = env->next;
	}
	return (new);
}

t_env	*insert_front_env(t_env *new, char *var, char *msg, int type)
{
	t_env	*node;

	node = (t_env *) malloc (sizeof (t_env));
	if (!node)
		return (0);
	node->variable = NULL;
	node->value = NULL;
	node->type = type;
	if (var)
		node->variable = ft_strdup(var);
	if (msg)
		node->value = ft_strdup(msg);
	node->next = new;
	return (node);
}

void	insert_last_env(t_env **lst, t_env *new)
{
	t_env	*list;

	if (!lst)
		return ;
	if (*lst)
	{
		list = *lst;
		while (list->next != NULL)
			list = list->next;
		list->next = new;
	}
	else
		*lst = new;
}
