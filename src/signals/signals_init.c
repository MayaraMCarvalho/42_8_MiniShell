/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:44 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:45 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/signals.h"

#include <unistd.h>
#include <signal.h>

void	sign_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	sign_delimiter(void)
{
	signal(SIGINT, sign_interrupt_delimiter);
}

void	sign_init(void)
{
	signal(SIGINT, sign_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	sign_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
