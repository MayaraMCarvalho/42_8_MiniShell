/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:24 by macarval          #+#    #+#             */
/*   Updated: 2023/10/26 18:41:26 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include "env_init.h"

char	*get_paths(char **envp);
void	ft_execve(char **cmd, t_env **env_head, t_cmd_table *cmd_table);
char	*get_right_path(char **paths, char **cmd);

#endif
