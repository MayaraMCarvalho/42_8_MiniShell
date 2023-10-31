/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:15:08 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 10:15:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "minishell.h"

//SIG EXEC-
void	sign_interrupt(int signum);
void	sign_interrupt_delimiter(int signum);
void	ctrl_d(t_cmd_table *cmd_table);

//SIG INIT
void	sign_child(void);
void	sign_delimiter(void);
void	sign_init(void);
void	sign_ignore(void);

#endif
