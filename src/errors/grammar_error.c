#include "../../headers/error.h"

int	syntax_error(char *token, t_cmd_table *cmd_table)
{
	printf("bash: syntax error near unexpected token `%s'\n", token);
	cmd_table->latest_exit_code = 258;
	return (1);
}
