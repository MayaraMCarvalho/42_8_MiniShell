/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:39 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 18:15:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELIMITER_H
# define DELIMITER_H

# include "parser.h"

bool	del_is_input(t_redirect *redirect_arr, int redirect_count);
int		delimiter(t_redirect *redir_arr, int redir_n, t_cmd_table *cmd_table);
int		delimiter_count(t_redirect *redirect_arr, int redirect_count);
void	delimiter_single_builtin(t_cmd_table *cmd_table, int io[2]);

#endif
