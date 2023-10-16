#ifndef PIPES_H
# define PIPES_H

# define READ 0
# define WRITE 1

# include "parser.h"

void	free_pids_and_pipes(t_cmd_table *cmd_table);
void	close_all_pipes(t_cmd_table *cmd_table);
void	redirect_first_cmd(t_cmd_table *cmd_table, t_command *cmd);
void	redirect_middle_cmd(t_cmd_table *cmd_table, t_command *cmd, int cmd_i);
void	redirect_last_cmd(t_cmd_table *cmd_table, t_command *cmd);

void	close_pipes(t_cmd_table *cmd_table, int pipe_index, int pipe_to_close);
int		dup_and_close(int fd[2]);
int		close_one_pipe(int fd[2]);

#endif
