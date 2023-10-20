/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:37 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:38 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"
#include "../../headers/pipes.h"

void	free_func_cmd_table(t_cmd_table *cmd_table)
{
	t_command	cmd_arr;
	int			i;

	i = 0;
	while (i != cmd_table->cmd_count && cmd_table->cmd_arr)
	{
		cmd_arr = cmd_table->cmd_arr[i];
		free_double_array(cmd_arr.single_cmd);
		if (cmd_arr.redirect_arr)
			free_redirect_arr(cmd_arr.redirect_arr, cmd_arr.redirect_count);
		i++;
	}
	free(cmd_table->input_string);
	free(cmd_table->cmd_arr);
	free_pids_and_pipes(cmd_table);
	cmd_table->cmd_arr = NULL;
}

void	free_redirect_arr(t_redirect *redir_arr, unsigned int redir_count)
{
	unsigned int	i;

	i = 0;
	while (i < redir_count)
	{
		free(redir_arr[i].file_name);
		i++;
	}
	free(redir_arr);
}

void	free_double_array(char	**double_array)
{
	int	i;

	i = 0;
	while (double_array[i])
	{
		free(double_array[i]);
		i++;
	}
	free(double_array);
}

int	num_of_arguments(t_token **head, int i)
{
	t_token	*iterate;
	int		num_of_arguments;

	iterate = get_cmd_location(head, i);
	num_of_arguments = 0;
	while (iterate != NULL && iterate->type != PIPE)
	{
		if (iterate->type == WORD)
			num_of_arguments++;
		iterate = iterate->next;
	}
	return (num_of_arguments);
}

t_token	*get_cmd_location(t_token **head, int i)
{
	t_token	*iterate;
	int		cmd_n;

	iterate = *head;
	cmd_n = 0;
	while (iterate != NULL && i != cmd_n)
	{
		if (iterate->type == PIPE)
			cmd_n++;
		iterate = iterate->next;
	}
	return (iterate);
}
