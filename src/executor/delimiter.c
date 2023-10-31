/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:04:59 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 09:09:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/signals.h"
#include "../../headers/expansions.h"
#include "../../headers/pipes.h"
#include "../../headers/builtin.h"

#include <readline/readline.h>
#include <stdbool.h>

int	delimiter_count(t_redirect *redirect_arr, int redirect_count)
{
	int	i;
	int	del_count;

	i = 0;
	del_count = 0;
	while (i < redirect_count)
	{
		if (redirect_arr[i++].type == DELIMITER)
			del_count++;
	}
	return (del_count);
}

bool	del_is_input(t_redirect *redirect_arr, int redirect_count)
{
	t_type	type;

	while (redirect_count > 0)
	{
		type = redirect_arr[redirect_count - 1].type;
		if (type == DELIMITER)
			return (true);
		if (type == INFILE)
			return (false);
		redirect_count--;
	}
	return (false);
}

static void	exec_delim(char *eof, int del_n, int fd[2], t_cmd_table *cmd_table)
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
		if (del_n == 0)
		{
			input_string = expand_var_quotes(input_string, cmd_table);
			ft_putstr_fd(input_string, fd[WRITE]);
			ft_putstr_fd("\n", fd[WRITE]);
		}
		free(input_string);
	}
	free(input_string);
}

int	delimiter(t_redirect *redir_arr, int redir_n, t_cmd_table *cmd_table)
{
	int		i;
	int		del_count;
	int		fd[2];

	sign_delimiter();
	del_count = delimiter_count(redir_arr, redir_n);
	if (!del_count)
		return (0);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	i = 0;
	while (del_count > 0)
	{
		if (redir_arr[i].type == DELIMITER)
			exec_delim(redir_arr[i].file_name, --del_count, fd, cmd_table);
		i++;
	}
	if (!del_is_input(redir_arr, redir_n))
		return (close_one_pipe(fd));
	return (dup_and_close(fd));
}

void	delimiter_single_builtin(t_cmd_table *cmd_table, int io[2])
{
	t_redirect	*redirect_arr;
	int			i;

	close(io[READ]);
	close(io[WRITE]);
	sign_delimiter();
	redirect_arr = cmd_table->cmd_arr[0].redirect_arr;
	i = 0;
	while (i < cmd_table->cmd_arr[0].redirect_count)
	{
		if (redirect_arr[i].type == DELIMITER)
			exec_delimiter_single_builtin(redirect_arr[i].file_name);
		i++;
	}
	exit(0);
}
