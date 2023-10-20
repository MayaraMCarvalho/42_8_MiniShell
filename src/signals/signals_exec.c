/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:42 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:43 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/signals.h"

#include <unistd.h>
#include <stdlib.h>

void	sign_interrupt(int signum)
{
	signum -= signum;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sign_interrupt_delimiter(int signum)
{
	close(STDOUT_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(128 + signum);
}

void	ctrl_d(int latest_exit_code)
{
	write(STDERR_FILENO, "exit\n", 5);
	exit(latest_exit_code);
}
