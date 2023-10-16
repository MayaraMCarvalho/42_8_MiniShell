/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	c_cd(t_shell *shell)
{
	if (!strcmp_mod(shell->command, "cd"))
	{
		update_(*shell);
		if (strcmp_mod(shell->flag, "-") && !is_flag_null(shell))
			return (1);
		if (!shell->content && !shell->flag)
			shell->content = ft_strdup(getenv("HOME"));
		else if (!strcmp_mod(shell->flag, "-"))
			get_oldpwd(shell);
		exe_cd(*shell);
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
		shell->content = ft_strdup(var->msg);
		printf("%s\n", shell->content);
	}
	else
	{
		printf("bash: cd: OLDPWD not set\n");
		shell->exit_code = 1;
	}
}

void	exe_cd(t_shell shell)
{
	t_lst	*var;
	char	*oldpwd;
	char	buf[256];
	int		control;

	control = -1;
	var = find_arg(shell, "PWD");
	oldpwd = var->msg;
	if (shell.content)
	{
		control = chdir(shell.content);
		if (control == -1)
		{
			printf("bash: cd: %s: No such file or directory\n", shell.content);
			shell.exit_code = 1;
		}
	}
	if (control == 0)
	{
		update_var(shell, "OLDPWD", oldpwd);
		update_var(shell, "PWD", getcwd(buf, 256));
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
