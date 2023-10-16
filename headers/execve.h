#ifndef EXECVE_H
# define EXECVE_H

# include "env_init.h"

char	*get_paths(char **envp);
void	ft_execve(char **cmd, t_env **env_head);
char	*get_right_path(char **paths, char **cmd);

#endif
