/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:10 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 17:29:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_export(t_shell *shell, t_cmd_table *cmd_table)
{
	if (!strcmp_mod(shell->command, "export"))
	{
		update_(*shell);
		if (!is_flag_null(shell))
			return (1);
		if (!shell->content)
		{
			sort_export(shell->env);
			shell->exit_code = 0;
		}
		else
			get_args(shell, cmd_table);
		return (1);
	}
	return (0);
}

void	get_args(t_shell *shell, t_cmd_table *cmd_table)
{
	int		i;
	char	**arg;
	char	*var;
	char	*msg;

	arg = cmd_table->cmd_arr[shell->cmd_index].single_cmd;
	i = 0;
	while (arg[++i])
	{
		var = strchr_rev(arg[i], '=');
		if (!var)
			var = ft_strdup(arg[i]);
		msg = strchr_mod(arg[i], '=');
		free(shell->content);
		shell->content = ft_strdup(var);
		add_export(shell, var, msg);
		free(var);
	}
}

int	add_export(t_shell *shell, char *var, char	*msg)
{
	t_lst	*node;
	t_lst	*new_node;


	if (is_args(shell))
	{
		node = find_arg(*shell, var);
		new_node = NULL;
		new_node = insert_front(new_node, var, msg, GLOBAL);
		add_node(*shell, node, new_node);
		free_list(new_node);
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
