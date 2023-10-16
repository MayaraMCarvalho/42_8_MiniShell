#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "parser.h"

bool	is_builtin(char *arg);
void	execute_builtin(t_cmd_table *cmd_table, int cmd_index, int io[2]);
void	builtin_single_cmd(t_cmd_table *cmd_table);
void	exec_delimiter_single_builtin(char *eof);

char	*get_home_cmd_table(t_env **env_head);

#endif
