/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:13:37 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 11:01:55 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_exit(t_shell *shell, t_cmd_table *cmd_table)
{
	int		control;

	control = 0;
	if (!strcmp_mod(shell->command, "exit"))
	{
		control = 1;
		if (shell->content)
			get_exit_code(shell);
		free_list(shell->env);
		free_shell(*shell);
		free_table(cmd_table);
		rl_clear_history();
	}
	return (control);
}

void	get_exit_code(t_shell *shell)
{
	char	**split;

	split = ft_split(shell->content, ' ');
	if (!isdigit_mod(split[0]))
	{
		ft_putstr_fd("bash: exit: numeric argument required\n", STDERR_FILENO);
		shell->exit_code = 2;
	}
	else if (split[1])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_code = 1;
	}
	else
		shell->exit_code = ft_atoi(shell->content);
	free_array(&split);
}

void	free_table(t_cmd_table *cmd_table)
{
	free(cmd_table->home);
	free_env(cmd_table->env);
	free_func_token(cmd_table->token_head);
	free_func_cmd_table(cmd_table);
	free(cmd_table);
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
