/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 18:16:25 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*make_text(void)
{
	char	*home;
	char	buf[256];
	char	*path;
	char	*temp;
	char	*text;

	path = ft_strdup(getcwd(buf, 256));
	home = getenv("HOME");
	if (ft_strnstr(path, home, ft_strlen(home)) || !strcmp_mod(path, home))
	{
		temp = ft_substr(path, ft_strlen(home), ft_strlen(path));
		free(path);
		path = ft_strdup(temp);
		free(temp);
	}
	text = get_name();
	temp = ft_strjoin(text, path);
	free(path);
	free(text);
	text = ft_strjoin(temp, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp);
	return (text);
}

char	*get_name(void)
{
	char	*temp1;
	char	*temp2;
	char	*user;

	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
	user = getenv("USERNAME");
	if (!user)
		user = getenv("NAME");
	temp2 = ft_strjoin(temp1, user);
	free(temp1);
	temp1 = ft_strjoin("\033[1;33m", temp2);
	free(temp2);
	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
	free(temp1);
	return (temp2);
}

void	inicialize(t_shell *shell)
{
	shell->line = NULL;
	shell->lex = NULL;
	shell->command = NULL;
	shell->flag = NULL;
	shell->content = NULL;
}

void	verify_builtins(t_shell *shell, t_cmd_table *cmd_table)
{
	if (shell->command && is_command(shell, cmd_table))
	{
		ft_putstr_fd(shell->command, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		shell->exit_code = 127;
	}
}

int	make_shell(t_shell *shell)
{
	if (!check_void(shell->line, 0))
	{
		shell->lex = tokenization(shell);
		return (1);
	}
	return (0);
}
