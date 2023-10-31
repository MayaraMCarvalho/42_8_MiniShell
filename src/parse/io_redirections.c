/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:05:34 by macarval          #+#    #+#             */
/*   Updated: 2023/10/20 11:05:35 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

void	create_redir_arr(t_command *single_cmd_info, t_token **head, int i)
{
	t_token		*start;
	int			r_num;

	start = get_cmd_location(head, i);
	r_num = count_redirect(start);
	if (r_num)
	{
		single_cmd_info->redirect_arr = ft_malloc((r_num) * sizeof(t_redirect));
		single_cmd_info->redirect_count = r_num;
		fill_redirect_arr(single_cmd_info->redirect_arr, start);
	}
	else
	{
		single_cmd_info->redirect_arr = NULL;
		single_cmd_info->redirect_count = 0;
	}
}

int	count_redirect(t_token *start)
{
	t_token	*iterate;
	int		redirect_count;

	iterate = start;
	redirect_count = 0;
	while (iterate != NULL && iterate->type != PIPE)
	{
		if (iterate->type == INFILE || iterate->type == OUTFILE
			|| iterate->type == APPEND || iterate->type == DELIMITER)
			redirect_count++;
		iterate = iterate->next;
	}
	return (redirect_count);
}

void	fill_redirect_arr(t_redirect *redirect_arr, t_token *iterate)
{
	int	redirect_i;

	redirect_i = 0;
	while (iterate != NULL && iterate->type != PIPE)
	{
		if (iterate->type == INFILE || iterate->type == OUTFILE
			|| iterate->type == APPEND || iterate->type == DELIMITER)
		{
			redirect_arr[redirect_i].type = iterate->type;
			redirect_arr[redirect_i].file_name = ft_strdup(iterate->text);
			redirect_i++;
		}
		iterate = iterate->next;
	}
}
