/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:21:16 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 17:30:13 by macarval         ###   ########.fr       */
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
		error_built(shell->command, ": `",
			content, "': not a valid identifier\n");
		shell->exit_code = 1;
		return (0);
	}
	return (1);
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

	letter = '\0';
	if (!strcmp_mod(shell->command, "echo"))
		letter = verify_flags(shell->flag, NULL);
	else if (shell->content && shell->content[0] == '-'
		&& strcmp_mod(shell->command, "exit"))
		letter = verify_flags(shell->content, NULL);
	if (letter != '\0')
	{
		print_error_flag (shell, letter);
		return (0);
	}
	return (1);
}
