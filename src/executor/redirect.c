/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:16 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 14:38:50 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/redirect.h"
#include "../../headers/delimiter.h"
#include "../../headers/pipes.h"
#include "../../headers/execute.h"
#include "../../headers/minishell.h"

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

static void	redirect_error(t_cmd_table *cmd_tab, char *file)
{
	close_all_pipes(cmd_tab);
	if (errno == ENOENT)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Permission denied \n", STDERR_FILENO);
	}
	free_table(cmd_tab);
	rl_clear_history();
	exit(1);
}

int	redirect_input(t_cmd_table *cmd_tab, t_redirect *red, int red_count)
{
	int	in_fd;
	int	i;

	in_fd = 0;
	i = -1;
	if (!count_red(red, red_count, INFILE, INFILE))
		return (0);
	while (++i < red_count)
	{
		if (red[i].type == INFILE)
		{
			in_fd = open(red[i].file_name, O_RDONLY);
			if (in_fd == -1)
				redirect_error(cmd_tab, red[i].file_name);
			if (in_fd && !del_is_input(red, red_count))
				dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
	}
	return (1);
}

int	redirect_output(t_cmd_table *cmd_tab, t_redirect *red, int red_count)
{
	int	fd;
	int	i;

	fd = 0;
	i = -1;
	if (!count_red(red, red_count, OUTFILE, APPEND))
		return (0);
	while (++i < red_count)
	{
		if (red[i].type == OUTFILE)
			fd = open(red[i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red[i].type == APPEND)
			fd = open(red[i].file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			redirect_error(cmd_tab, red[i].file_name);
		if (fd)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
			fd = 0;
		}
	}
	return (1);
}

void	redirect_child(t_cmd_table *cmd_table, int cmd_i)
{
	t_redirect	*red;
	int			fd_delimiter;
	int			red_count;

	red = cmd_table->cmd_arr[cmd_i].redirect_arr;
	red_count = cmd_table->cmd_arr[cmd_i].redirect_count;
	fd_delimiter = delimiter(red, red_count, cmd_table);
	if (fd_delimiter > 0)
		dup2(fd_delimiter, STDIN_FILENO);
	if (cmd_i == 0)
		redirect_first_cmd(cmd_table, &cmd_table->cmd_arr[cmd_i]);
	else if (cmd_i != cmd_table->cmd_count - 1)
		redirect_middle_cmd(cmd_table, &cmd_table->cmd_arr[cmd_i], cmd_i);
	else
		redirect_last_cmd(cmd_table, &cmd_table->cmd_arr[cmd_i]);
}

void	redirect_single_child(t_cmd_table *cmd_table)
{
	t_redirect	*redirect_arr;
	int			redirect_count;
	int			fd_delimiter;

	redirect_arr = cmd_table->cmd_arr[0].redirect_arr;
	redirect_count = cmd_table->cmd_arr[0].redirect_count;
	if (!redirect_count)
		return ;
	fd_delimiter = delimiter(redirect_arr, redirect_count, cmd_table);
	if (fd_delimiter > 0)
		dup2(fd_delimiter, STDIN_FILENO);
	redirect_input(cmd_table, redirect_arr, redirect_count);
	redirect_output(cmd_table, redirect_arr, redirect_count);
}
