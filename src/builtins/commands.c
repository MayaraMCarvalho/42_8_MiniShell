/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 17:36:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_command(t_shell *shell, t_cmd_table *cmd_table)
{
	if (c_echo(shell))
		return (0);
	else if (c_cd(shell))
		return (0);
	else if (c_pwd(shell))
		return (0);
	else if (c_export(shell, cmd_table))
		return (0);
	else if (c_unset(shell, cmd_table))
		return (0);
	else if (c_env(shell))
		return (0);
	else if (c_exit(shell, cmd_table))
		exit(shell->exit_code);
	else if (c_history(shell))
		return (0);
	return (1);
}

void	update_(t_shell shell)
{
	char	*var;

	if (shell.content == NULL && ft_strchr(shell.command, '='))
		update_var(shell, "_", NULL);
	else
	{
		var = ft_strjoin("/usr/bin/", shell.command);
		if (var)
		{
			update_var(shell, "_", var);
			free(var);
		}
	}
}

int	c_pwd(t_shell *shell)
{
	char	buf[256];

	if (!strcmp_mod(shell->command, "pwd"))
	{
		if (!is_flag_null(shell))
			return (1);
		printf("%s\n", getcwd(buf, 256));
		return (1);
	}
	return (0);
}

int	c_history(t_shell *shell)
{
	HISTORY_STATE	*myhist;
	HIST_ENTRY		**mylist;
	int				i;

	if (!strcmp_mod(shell->command, "history"))
	{
		myhist = history_get_history_state();
		mylist = history_list();
		i = 0;
		while (myhist && myhist && i < myhist->length)
		{
			printf("%5i  %s  %s\n",
				i + 1, mylist[i]->line, mylist[i]->timestamp);
			i++;
		}
		if (myhist)
			free (myhist);
		return (1);
	}
	return (0);
}
