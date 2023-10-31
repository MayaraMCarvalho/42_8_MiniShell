/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:24 by macarval          #+#    #+#             */
/*   Updated: 2023/10/27 09:20:02 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include "env_init.h"

char	*get_paths(char **envp);
char	*get_right_path(char **paths, char **cmd);
void	ft_execve(char **cmd, t_env **env_head, t_cmd_table *cmd_table);
void	free_execve(char *cmd, char **split, char **envp, t_cmd_table *table);

#endif
