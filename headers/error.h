#ifndef ERROR_H
# define ERROR_H

# include "parser.h"

int		export_error_check(char *arg);
int		syntax_error(char *token, t_cmd_table *cmd_table);
void	execve_error(char *cmd);
void	cd_error_msg(t_cmd_table *cmd_table, char *arg, char *error_msg);

#endif
