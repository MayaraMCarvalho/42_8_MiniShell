/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 21:18:55 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execute.h"
#include "../headers/signals.h"
#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token		*token_head;
	t_cmd_table	*cmd_table;
	t_shell		shell;
	char		*text;

	token_head = NULL;
	cmd_table = init_cmd_table(&token_head, envp);
	while (true && argc && argv)
	{
		text = make_text();
		sign_init();
		shell.line = strtrim_mod(readline(text), " ");
		cmd_table->input_string = shell.line;
		free(text);
		if (shell.line[0] != '\0')
		{
			add_history(shell.line);
			if (!tokenize_string(shell.line, cmd_table))
				exec_minishell(cmd_table, token_head);
			free_func_token(&token_head);
		}
		else
			free(shell.line);
	}
	return (0);
}

void	exec_minishell(t_cmd_table *cmd_table, t_token *token_head)
{
	fill_cmd_table(cmd_table, &token_head);
	execute(cmd_table);
	free_func_cmd_table(cmd_table);
}
