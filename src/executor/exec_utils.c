#include "../../headers/execute.h"

#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

void	create_pid_array(t_cmd_table *cmd_table)
{
	cmd_table->pids = ft_malloc(sizeof(pid_t) * cmd_table->cmd_count);
}

void	create_pipes(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	cmd_table->pipes = ft_malloc(sizeof(int) * (cmd_table->cmd_count - 1) * 2);
	while (i < cmd_table->cmd_count - 1)
	{
		if (pipe(cmd_table->pipes[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	wait_for_children(t_cmd_table *cmd_table)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_table->cmd_count)
		waitpid(cmd_table->pids[i++], &status, 0);
	cmd_table->latest_exit_code = WEXITSTATUS(status);
}

int	count_red(t_redirect *red, int red_count, t_type type1, t_type type2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < red_count)
	{
		if (red[i].type == type1 || red[i].type == type2)
			count++;
		i++;
	}
	return (count);
}

void	reset_stdin_stdout(int io[2])
{
	dup2(io[READ], STDIN_FILENO);
	dup2(io[WRITE], STDOUT_FILENO);
	close(io[READ]);
	close(io[WRITE]);
}
