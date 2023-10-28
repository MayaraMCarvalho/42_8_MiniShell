/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:32 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 17:39:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_unset(t_shell *shell, t_cmd_table *cmd_table)
{
	int		i;
	char	**arg;

	if (!is_flag_null(shell))
		return (1);
	if (!strcmp_mod(shell->command, "unset"))
	{
		update_(*shell);
		arg = cmd_table->cmd_arr[shell->cmd_index].single_cmd;
		i = 0;
		while (arg[++i])
		{
			free(shell->content);
			shell->content = ft_strdup(arg[i]);
			exe_unset(shell);
		}
		return (1);
	}
	return (0);
}

int	exe_unset(t_shell *shell)
{
	t_lst	*node;

	if (shell->content)
	{
		if (is_args(shell))
		{
			node = find_arg(*shell, shell->content);
			if (node != NULL)
			{
				if (shell->env == node)
					shell->env = node->next;
				else
					node->prev->next = node->next;
				if (node->next != NULL)
					node->next->prev = node->prev;
				free(node->var);
				free(node->msg);
				free(node);
			}
		}
	}
	return (0);
}

void	verify_expansion(char **token)
{
	int		i;
	char	*final;

	i = 0;
	while (token[i])
	{
		final = ft_strchr(token[i], '/');
		if (!strcmp_mod(token[i], "~") || !strcmp_mod(token[i], "~/")
			|| (final && token[i][0] == '~'))
		{
			final = ft_strjoin(getenv("HOME"), final);
			free(token[i]);
			token[i] = final;
		}
		i++;
	}
}
