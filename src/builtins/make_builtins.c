/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:33:18 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 15:10:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_line(t_cmd_table *cmd_table, int cmd_index)
{
	char	*line;
	char	**arg;
	char	*temp;
	char	*temp2;

	arg = cmd_table->cmd_arr[cmd_index].single_cmd;
	line = NULL;
	while (*arg)
	{
		temp = ft_strjoin(*arg, " ");
		temp2 = ft_strjoin(line, temp);
		free(temp);
		free(line);
		line = ft_strdup(temp2);
		free(temp2);
		arg++;
	}
	return (line);
}

int	call_builtins(t_cmd_table *cmd_table, char *line, int cmd_index)
{
	t_shell	shell;

	inicialize(&shell);
	shell.env = make_list(cmd_table->env);
	shell.line = line;
	shell.cmd_index = cmd_index;
	shell.exit_code = cmd_table->latest_exit_code;
	if (make_shell(&shell))
		make_builtins(&shell, cmd_table);
	free_env(cmd_table->env);
	cmd_table->env = tranfer_env(shell.env);
	free_list(shell.env);
	free_shell(shell);
	return (shell.exit_code);
}

void	make_builtins(t_shell *shell, t_cmd_table *cmd_table)
{
	int		i;
	int		tam;
	char	*line;

	i = 0;
	if (!strcmp_mod(shell->lex[i][1], BUILTIN))
		shell->command = ft_strdup(shell->lex[i++][0]);
	while (shell->lex[i] && !strcmp_mod(shell->lex[i][1], FLAG))
		join_flag(shell, i++);
	if (!strcmp_mod(shell->command, "echo"))
	{
		line = ft_substr(shell->line, 0, ft_strlen(shell->line) - 1);
		tam = ft_strlen(shell->command) + 1;
		if (shell->flag)
			tam += ft_strlen(shell->flag) + 1;
		shell->content = ft_substr(line, tam, ft_strlen(shell->line));
		free(line);
	}
	else
	{
		while (shell->lex[i] && !strcmp_mod(shell->lex[i][1], CONTENT))
			join_content(shell, i++);
	}
	verify_builtins(shell, cmd_table);
	free_join(shell);
}

void	join_flag(t_shell *shell, int i)
{
	char	*temp;
	char	*temp2;

	if (shell->flag)
	{
		temp = ft_strjoin(" ", shell->lex[i][0]);
		temp2 = ft_strjoin(shell->flag, temp);
		free(shell->flag);
		free(temp);
		shell->flag = ft_strdup(temp2);
		free(temp2);
	}
	else
		shell->flag = ft_strdup(shell->lex[i][0]);
}

void	join_content(t_shell *shell, int i)
{
	char	*temp;
	char	*temp2;

	if (shell->content)
	{
		temp = ft_strjoin(" ", shell->lex[i][0]);
		temp2 = ft_strjoin(shell->content, temp);
		free(shell->content);
		free(temp);
		shell->content = ft_strdup(temp2);
		free(temp2);
	}
	else
		shell->content = ft_strdup(shell->lex[i][0]);
}
