/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:32 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 18:15:33 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

void	env_lstadd_back(t_env *lst, t_env *new);
t_env	*env_lstlast(t_env *lst);
t_env	*env_lstnew(char *s);
int		lst_size(t_env **env_head);
void	lst_delone(t_env **env_head, char *variable);

#endif
