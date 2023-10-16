/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:13:37 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 12:26:03 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_exit(t_shell *shell, t_cmd_table *cmd_table)
{
	int		control;

	control = 0;
	if (!strcmp_mod(shell->command, "exit"))
	{
		if (!is_flag_null(shell))
			return (1);
		control = 1;
		free_list(shell->env);
		free_shell(*shell);
		free_env(cmd_table->env);
		free_func_cmd_table(cmd_table);
		rl_clear_history();
	}
	return (control);
}

void	free_list(t_lst *list)
{
	t_lst	*temp;
	t_lst	*next;

	temp = list;
	while (temp != NULL)
	{
		free(temp->var);
		if (temp->msg)
			free(temp->msg);
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	free_shell(t_shell shell)
{
	free(shell.line);
	if (shell.command)
		free(shell.command);
	if (shell.flag)
		free(shell.flag);
	if (shell.content)
		free(shell.content);
	if (shell.lex)
		free_double(&shell.lex);
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
