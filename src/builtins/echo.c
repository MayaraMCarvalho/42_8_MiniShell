/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/10/28 10:35:31 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_echo(t_shell *shell)
{
	if (!strcmp_mod(shell->command, "echo"))
	{
		if (shell->flag && print_flag(*shell))
		{
			free(shell->flag);
			shell->flag = ft_strdup("-n");
		}
		if (strcmp_mod(shell->content, "$_"))
			update_(*shell);
		if (!strcmp_mod(shell->content, "$?"))
		{
			printf("%i", shell->exit_code);
			shell->exit_code = 0;
		}
		else if (shell->content)
			printf("%s", shell->content);
		if (!shell->flag || verify_flags(shell->flag, "n"))
			printf("\n");
		return (1);
	}
	return (0);
}

int	print_flag(t_shell shell)
{
	char	**split;
	int		i;
	int		control;

	split = ft_split(shell.flag, ' ');
	i = -1;
	control = 0;
	while (split[++i] && !verify_flags(split[i], "n"))
		control++;
	while (split[i])
		printf("%s ", split[i++]);
	free_array(&split);
	return (control);
}

void	print_error_flag(t_shell *shell, char letter)
{
	char	let[2];

	let[0] = letter;
	let[1] = '\0';
	if (!strcmp_mod(shell->command, "env"))
	{
		error_built(shell->command, ": invalid option -- '", let, "'\n");
		shell->exit_code = 125;
	}
	else
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		error_built(shell->command, ": -", let, ": invalid option\n");
		shell->exit_code = 2;
	}
}

void	error_built(char *var1, char *txt1, char *var2, char *txt2)
{
	ft_putstr_fd(var1, STDERR_FILENO);
	ft_putstr_fd(txt1, STDERR_FILENO);
	ft_putstr_fd(var2, STDERR_FILENO);
	ft_putstr_fd(txt2, STDERR_FILENO);
}
