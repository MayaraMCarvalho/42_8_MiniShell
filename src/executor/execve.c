/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:07 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execve.h"
#include "../../headers/env_utils.h"
#include "../../headers/error.h"

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

void	ft_execve(char **cmd, t_env **env_head)
{
	char	**envp;
	char	*path;
	char	**splitted_paths;
	char	*cmdpath;

	if (!cmd[0])
		exit(0);
	path = NULL;
	splitted_paths = NULL;
	envp = linked_list_to_double_array(env_head);
	path = get_paths(envp);
	if (path)
		splitted_paths = ft_split(path + 5, ':');
	cmdpath = get_right_path(splitted_paths, cmd);
	execve(cmdpath, cmd, envp);
	free(cmdpath);
	free_envp(envp);
	execve_error(cmd[0]);
}
