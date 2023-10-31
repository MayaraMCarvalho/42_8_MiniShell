/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:04:56 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 15:18:01 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtin.h"
#include "../../headers/redirect.h"
#include "../../headers/delimiter.h"
#include "../../headers/execute.h"
#include "../../headers/parser.h"
#include "../../headers/minishell.h"
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*get_home_cmd_table(t_env **env_head)
{
	t_env	*iter;

	iter = *env_head;
	while (iter)
	{
		if (ft_strncmp(iter->variable, "HOME", 5) == 0)
			break ;
		iter = iter->next;
	}
	return (ft_strdup(iter->value));
}

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strncmp("echo", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("cd", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("pwd", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("export", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("unset", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("env", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	if (ft_strncmp("exit", arg, ft_strlen(arg) + 1) == 0)
		return (true);
	return (false);
}

void	execute_builtin(t_cmd_table *cmd_table, int cmd_index, int io[2])
{
	char	*line;

	line = get_line(cmd_table, cmd_index);
	cmd_table->latest_exit_code = call_builtins(cmd_table, line, cmd_index);
	if (cmd_table->cmd_count == 1)
		reset_stdin_stdout(io);
	if (cmd_table->cmd_count > 1)
		exit(0);
}

void	builtin_single_cmd(t_cmd_table *cmd_table)
{
	t_redirect	*redirect_arr;
	int			redirect_count;
	pid_t		pid;
	int			io[2];

	redirect_arr = cmd_table->cmd_arr[0].redirect_arr;
	redirect_count = cmd_table->cmd_arr[0].redirect_count;
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (delimiter_count(redirect_arr, redirect_count) > 0)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			delimiter_single_builtin(cmd_table, io);
		wait(NULL);
	}
	redirect_input(cmd_table, redirect_arr, redirect_count);
	redirect_output(cmd_table, redirect_arr, redirect_count);
	execute_builtin(cmd_table, 0, io);
}

void	exec_delimiter_single_builtin(char *eof)
{
	char	*input_string;

	input_string = NULL;
	while (1)
	{
		input_string = readline("> ");
		if (!input_string)
			exit(130);
		if (!ft_strncmp(input_string, eof, ft_strlen(eof) + 1))
			break ;
		free(input_string);
	}
	free(input_string);
}
