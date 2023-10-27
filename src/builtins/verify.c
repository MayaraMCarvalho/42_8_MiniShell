/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:35:31 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 18:17:15 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	verify_commands(char *token)
{
	char	*path;
	char	*temp;
	char	**split;
	int		i;

	path = getenv("PATH");
	split = ft_split(path, ':');
	i = -1;
	while (split[++i])
	{
		temp = ft_strjoin(split[i], "/");
		path = ft_strjoin(temp, token);
		free(temp);
		if (strcmp_mod(token, "com")
			&& !access(path, X_OK))
		{
			free_array(&split);
			free(path);
			return (1);
		}
		free(path);
	}
	free_array(&split);
	return (0);
}

int	verify_list(char *token, char **list)
{
	int	i;

	i = -1;
	while (list[++i])
	{
		if (!strcmp_mod(token, list[i]))
		{
			free_array(&list);
			return (1);
		}
	}
	free_array(&list);
	return (0);
}

int	verify_exceptions(char *token)
{
	if (!strcmp_mod(token, "") || ft_strchr(token, ' ') != NULL
		|| ft_strchr(token, ' ') != NULL || ft_strnstr(token, "./", 2)
		|| !strcmp_mod(token, ".") || !strcmp_mod(token, "..")
		|| !strcmp_mod(token, "./") || !strcmp_mod(token, "../")
		|| ft_strnstr(token, "../", 3))
		return (1);
	return (0);
}

int	check_void(char *str, int i)
{
	if ((str[i] == '\'' && str[i + 1] && str[i + 1] == '\'')
		|| (str[i] == '"' && str[i + 1] && str[i + 1] == '"'))
		return (1);
	return (0);
}
