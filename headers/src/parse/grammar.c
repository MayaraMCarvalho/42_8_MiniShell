#include "../../headers/parser.h"
#include "../../headers/error.h"

int	grammar_check(t_token **head, t_cmd_table *cmd_table)
{
	if (double_metachar_check(head, cmd_table))
		return (1);
	return (0);
}

int	double_metachar_check(t_token **head, t_cmd_table *cmd_table)
{
	t_token	*iterate;

	iterate = *head;
	if (iterate && iterate->type == PIPE)
		return (syntax_error(iterate->text, cmd_table));
	while (iterate != NULL)
	{
		if ((iterate->type == PIPE || iterate->type == REDIRECT)
			&& iterate->next == NULL)
			return (syntax_error("newline", cmd_table));
		else if ((iterate->type == PIPE || iterate->type == REDIRECT)
			&& iterate->next->type == PIPE)
			return (syntax_error(iterate->next->text, cmd_table));
		else if (iterate->type == REDIRECT && iterate->next->type == REDIRECT)
			return (syntax_error(iterate->next->text, cmd_table));
		iterate = iterate->next;
	}
	return (0);
}
