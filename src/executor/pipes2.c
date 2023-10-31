/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:13 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 16:25:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/pipes.h"
#include "../../headers/redirect.h"
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define BOTH 2

void	close_pipes(t_cmd_table *cmd_table, int pipe_index, int pipe_to_close)
{
	if (pipe_to_close == READ)
		close(cmd_table->pipes[pipe_index][READ]);
	else if (pipe_to_close == WRITE)
		close(cmd_table->pipes[pipe_index][WRITE]);
	else if (pipe_to_close == BOTH)
	{
		close(cmd_table->pipes[pipe_index][READ]);
		close(cmd_table->pipes[pipe_index][WRITE]);
	}
}

int	dup_and_close(int fd[2])
{
	int	rd;

	rd = dup(fd[READ]);
	close(fd[READ]);
	close(fd[WRITE]);
	return (rd);
}

int	close_one_pipe(int fd[2])
{
	close(fd[READ]);
	close(fd[WRITE]);
	return (0);
}
