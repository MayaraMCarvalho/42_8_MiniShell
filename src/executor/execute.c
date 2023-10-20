/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:04 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:05 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execute.h"
#include "../../headers/builtin.h"
#include "../../headers/execve.h"
#include "../../headers/redirect.h"
#include "../../headers/signals.h"
#include "../../headers/pipes.h"

#include <sys/wait.h>

static void	execute_with_child(t_cmd_table *cmd_table, int cmd_i)
{
	char	**cmd;

	cmd = cmd_table->cmd_arr[cmd_i].single_cmd;
	sign_child();
	redirect_child(cmd_table, cmd_i);
	if (is_builtin(cmd_table->cmd_arr[cmd_i].single_cmd[0]))
	{
		execute_builtin(cmd_table, cmd_i, 0);
	}
	ft_execve(cmd, &cmd_table->env);
}

static void	execute_single_child(t_cmd_table *cmd_table)
{
	sign_child();
	redirect_single_child(cmd_table);
	ft_execve(cmd_table->cmd_arr[0].single_cmd, &cmd_table->env);
}

void	execute_multiple_cmd(t_cmd_table *cmd_table)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < cmd_table->cmd_count)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_with_child(cmd_table, i);
		cmd_table->pids[i] = pid;
		i++;
	}
	close_all_pipes(cmd_table);
	wait_for_children(cmd_table);
}

void	execute_single_cmd(t_cmd_table *cmd_table)
{
	int		status;
	pid_t	pid;

	if (is_builtin(cmd_table->cmd_arr[0].single_cmd[0]))
	{
		builtin_single_cmd(cmd_table);
		return ;
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_single_child(cmd_table);
	waitpid(pid, &status, 0);
	cmd_table->latest_exit_code = WEXITSTATUS(status);
}

void	execute(t_cmd_table *cmd_table)
{
	sign_ignore();
	if (cmd_table->cmd_count == 1)
		execute_single_cmd(cmd_table);
	else
		execute_multiple_cmd(cmd_table);
}
