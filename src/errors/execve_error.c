/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:04:42 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 10:42:22 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error.h"

#include <errno.h>

void	execve_error(char *cmd)
{
	if (errno == ENOENT || !cmd[0])
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		if (ft_strchr(cmd, '/'))
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free(cmd);
		exit(127);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied \n", STDERR_FILENO);
		free(cmd);
		exit(126);
	}
	free(cmd);
	exit(1);
}

void	cd_error_msg(t_cmd_table *cmd_table, char *arg, char *error_msg)
{
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	cmd_table->latest_exit_code = 1;
}
