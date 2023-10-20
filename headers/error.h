/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:29 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 18:15:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "parser.h"

int		export_error_check(char *arg);
int		syntax_error(char *token, t_cmd_table *cmd_table);
void	execve_error(char *cmd);
void	cd_error_msg(t_cmd_table *cmd_table, char *arg, char *error_msg);

#endif
