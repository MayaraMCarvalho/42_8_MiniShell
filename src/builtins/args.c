/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:21:16 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 15:33:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_lst	*find_arg(t_shell shell, char *var)
{
	t_lst	*temp;

	temp = shell.env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	is_args(t_shell *shell)
{
	char	*content;
	t_lst	*var;

	content = shell->content;
	if (content[0] == '=' || !ft_isalpha(content[0])
		|| isalnum_mod(content) || (!strcmp_mod(shell->command, "unset")
			&& ft_strchr(content, '=')))
	{
		var = find_arg(*shell, content + 1);
		if (content[0] == '$' && var)
			content = var->msg;
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(shell->command, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(content, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (0);
	}
	return (1);
}

void	apart_args(t_shell *shell, char c, int (*function)(t_shell *))
{
	int		i;
	char	**split;
	int		control;

	i = -1;
	if (shell->content)
	{
		split = ft_split(shell->content, c);
		while (split[++i])
		{
			free(shell->content);
			shell->content = ft_strdup(split[i]);
			control = function(shell);
			if (control == 1 && split[i + 1])
				printf(" ");
			else if (control == 0 && !split[i + 1]
				&& !strcmp_mod(shell->command, "echo"))
				printf("\b");
		}
		free_array(&split);
	}
}

char	verify_flags(char *flag, char *pattern)
{
	int		i;
	char	letter;

	i = 0;
	letter = '\0';
	if (flag)
	{
		if (flag[0] == '-')
			i++;
		if (!flag[i])
			return ('-');
		while (flag[i] && letter == '\0')
		{
			if (!ft_strchr(pattern, flag[i]))
				letter = flag[i];
			i++;
		}
	}
	return (letter);
}

int	is_flag_null(t_shell *shell)
{
	char	letter;

	letter = verify_flags(shell->flag, NULL);
	if (letter != '\0')
	{
		if (!strcmp_mod(shell->command, "env")
			|| !strcmp_mod(shell->command, "clear"))
		{
			printf("%s: invalid option -- '%c'\n", shell->command, letter);
			shell->exit_code = 1;
		}
		else
		{
			printf("bash: %s: -%c: invalid option\n", shell->command, letter);
			shell->exit_code = 2;
		}
		return (0);
	}
	return (1);
}
