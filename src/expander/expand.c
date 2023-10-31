/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:24 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 10:41:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expansions.h"
#include "../../headers/token.h"
#include "../../headers/error.h"
#include <stdio.h>

int	expand_env_var(char *str, char **temp, t_cmd_table *cmd_table)
{
	char	*var_value;
	char	*var_name;
	int		len_var_name;

	len_var_name = get_var_name(str, &var_name);
	var_value = find_var_value(var_name, cmd_table);
	if (var_value)
		*temp = var_value;
	else
		*temp = NULL;
	return (len_var_name);
}

int	expand_exit_status(char *str, char **temp, t_cmd_table *cmd_table)
{
	if (*(str + 1) == '?')
		*temp = ft_itoa(cmd_table->latest_exit_code);
	return (2);
}

int	get_var_name(char *str, char **var_name)
{
	int		i;

	i = 1;
	while (is_valid_var_name_char(str[i]) && str[i - 1] != '?')
		i++;
	*var_name = ft_substr(str, 1, (i - 1));
	return (i);
}

char	*find_var_value(char *var_name, t_cmd_table *cmd_table)
{
	t_env	*i;
	char	*var_val;

	i = cmd_table->env;
	if (!var_name[0])
		var_val = ft_strdup("$");
	else if (!ft_strncmp(var_name, "?", 1))
		var_val = ft_itoa(cmd_table->latest_exit_code);
	else
	{
		while (i != NULL)
		{
			if (!ft_strncmp(i->variable, var_name, ft_strlen(var_name) + 1))
			{
				if (i->value)
					var_val = ft_strdup(i->value);
				break ;
			}
			i = i->next;
		}
	}
	if (!i || !i->value)
		var_val = NULL;
	free (var_name);
	return (var_val);
}
