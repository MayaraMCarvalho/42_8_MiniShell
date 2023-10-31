/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:07 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 15:14:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/pipes.h"
#include "../../headers/execve.h"
#include "../../headers/env_utils.h"
#include "../../headers/error.h"
#include "../../headers/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

char	*get_right_path(char **paths, char **cmd)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!paths)
		return (ft_strdup(cmd[0]));
	while (paths[i])
	{
		ret = ft_strjoin_with_char(paths[i], cmd[0], '/');
		if (access(ret, X_OK | F_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (ft_strdup(cmd[0]));
}

char	*get_paths(char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (envp[i])
	{
		ret = ft_strnstr(envp[i], "PATH=", 5);
		if (ret)
			break ;
		i++;
	}
	return (ret);
}

static void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	ft_execve(char **cmd, t_env **env_head, t_cmd_table *cmd_table)
{
	char	**envp;
	char	*path;
	char	**splitted_paths;
	char	*cmdpath;
	char	*command;

	if (!cmd[0])
	{
		free_table(cmd_table);
		rl_clear_history();
		exit(0);
	}
	path = NULL;
	splitted_paths = NULL;
	envp = linked_list_to_double_array(env_head);
	path = get_paths(envp);
	if (path)
		splitted_paths = ft_split(path + 5, ':');
	cmdpath = get_right_path(splitted_paths, cmd);
	execve(cmdpath, cmd, envp);
	command = ft_strdup(cmd[0]);
	free_execve(cmdpath, splitted_paths, envp, cmd_table);
	execve_error(command);
}

void	free_execve(char *cmd, char **split, char **envp, t_cmd_table *table)
{
	free(cmd);
	free_array(&split);
	free_envp(envp);
	free_table(table);
	rl_clear_history();
}
