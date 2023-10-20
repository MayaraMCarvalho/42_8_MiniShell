/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:11 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 18:15:12 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "parser.h"

# define READ 0
# define WRITE 1

int		redirect_input(t_cmd_table *cmd_tab, t_redirect *red, int red_count);
int		redirect_output(t_cmd_table *cmd_tab, t_redirect *red, int red_count);
void	redirect_child(t_cmd_table *cmd_table, int cmd_i);
void	redirect_single_child(t_cmd_table *cmd_table);

#endif
