/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoferre <leoferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 02:28:09 by leoferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_cd(t_shell *shell)
{
	char	**split;

	if (!strcmp_mod(shell->command, "cd"))
	{
		update_(*shell);
		if (!shell->content)
			shell->content = ft_strdup(getenv("HOME"));
		else if (!strcmp_mod(shell->content, "-"))
			get_oldpwd(shell);
		split = ft_split(shell->content, ' ');
		if ((!strcmp_mod(split[0], "-") || split[0][0] != '-') && split[1])
		{
			ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
			shell->exit_code = 1;
			free_array(&split);
			return (1);
		}
		free_array(&split);
		if (strcmp_mod(shell->content, "-") && !is_flag_null(shell))
			return (1);
		exe_cd(shell);
		return (1);
	}
	return (0);
}

void	get_oldpwd(t_shell *shell)
{
	t_lst	*var;

	var = find_arg(*shell, "OLDPWD");
	if (var)
	{
		free(shell->content);
		shell->content = ft_strdup(var->msg);
		printf("%s\n", shell->content);
	}
	else
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
		shell->exit_code = 1;
	}
}

void	exe_cd(t_shell *shell)
{
	t_lst	*var;
	char	*oldpwd;
	char	buf[256];
	int		control;

	control = -1;
	var = find_arg(*shell, "PWD");
	oldpwd = var->msg;
	if (shell->content)
	{
		control = chdir(shell->content);
		if (control == -1)
		{
			ft_putstr_fd("bash: cd: ", STDERR_FILENO);
			ft_putstr_fd(shell->content, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			shell->exit_code = 1;
		}
	}
	if (control == 0)
	{
		update_var(*shell, "OLDPWD", oldpwd);
		update_var(*shell, "PWD", getcwd(buf, 256));
	}
}

void	update_var(t_shell shell, char *name, char *value)
{
	t_lst	*lst;
	t_lst	*node;

	lst = find_arg(shell, name);
	if (lst)
	{
		free(lst->msg);
		lst->msg = ft_strdup(value);
	}
	else
	{
		node = NULL;
		node = insert_front(node, name, value, ENVP);
		insert_last(&shell.env, node);
	}
}
