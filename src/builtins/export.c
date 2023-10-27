/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:10 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 16:27:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_export(t_shell *shell)
{
	if (!strcmp_mod(shell->command, "export"))
	{
		update_(*shell);
		if (!is_flag_null(shell))
			return (1);
		if (!shell->content || (shell->content[0] == '$'
				&& !find_arg(*shell, shell->content + 1)))
		{
			sort_export(shell->env);
			shell->exit_code = 0;
		}
		else
			apart_args(shell, ' ', add_export);
		return (1);
	}
	return (0);
}

void	print_export(t_lst *env)
{
	while (env != NULL)
	{
		if (strcmp_mod(env->var, "_"))
		{
			printf("declare -x %s", env->var);
			if (env->msg)
				printf("=\"%s\"", env->msg);
			printf("\n");
		}
		env = env->next;
	}
}

void	sort_export(t_lst *env)
{
	t_lst	*env_order;
	t_lst	*env_copy;
	t_lst	*node;

	node = NULL;
	env_order = NULL;
	env_copy = duplicate_env(env);
	while (env_copy != NULL)
	{
		node = get_min(env_copy);
		env_copy = remove_min(env_copy, node->var);
		insert_last(&env_order, node);
	}
	print_export(env_order);
	free_list(env_order);
}

int	add_export(t_shell *shell)
{
	t_lst	*node;
	t_lst	*new_node;
	char	*var;
	char	*msg;

	if (is_args(shell))
	{
		var = strchr_rev(shell->content, '=');
		if (!var)
			var = ft_strdup(shell->content);
		if (!var)
			return (0);
		msg = strchr_mod(shell->content, '=');
		node = find_arg(*shell, var);
		new_node = NULL;
		new_node = insert_front(new_node, var, msg, GLOBAL);
		add_node(*shell, node, new_node);
		free_list(new_node);
		free(var);
	}
	return (0);
}
