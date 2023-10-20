/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:04:47 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:04:48 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error.h"

int	syntax_error(char *token, t_cmd_table *cmd_table)
{
	printf("bash: syntax error near unexpected token `%s'\n", token);
	cmd_table->latest_exit_code = 258;
	return (1);
}
