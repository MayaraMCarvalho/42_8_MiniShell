/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/10/29 10:15:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <curses.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "parser.h"

# define ENVP 1
# define GLOBAL 2

# define FLAG "FLAG"
# define COMMAND "COMMAND"
# define BUILTIN "BUILTIN"
# define CONTENT "CONTENT"

typedef struct s_lex
{
	char			*token;
	char			*type;
	struct s_lex	*prev;
	struct s_lex	*next;
}	t_lex;

typedef struct s_shell
{
	t_lst		*env;
	char		*line;
	char		***lex;
	char		*command;
	char		*flag;
	char		*content;
	int			cmd_index;
	int			exit_code;
}	t_shell;

char		*get_line_text(t_cmd_table *cmd_table);
void		exec_minishell(t_cmd_table *cmd_table, t_token *token_head);

// args.c
int			is_args(t_shell *shell);
int			is_flag_null(t_shell *shell);
t_lst		*find_arg(t_shell shell, char *var);
char		verify_flags(char *flag, char *pattern);

// cd.c
int			c_cd(t_shell *shell);
void		exe_cd(t_shell *shell);
void		get_oldpwd(t_shell *shell);
void		update_var(t_shell shell, char *name, char *value);

// commands.c
int			c_pwd(t_shell *shell);
void		update_(t_shell shell);
int			c_history(t_shell *shell);
int			is_command(t_shell *shell, t_cmd_table *cmd_table);

// echo.c
int			c_echo(t_shell *shell);
int			print_flag(t_shell shell);
void		print_error_flag(t_shell *shell, char letter);
void		error_built(char *v1, char *t1, char *v2, char *t2);

// env.c
int			c_env(t_shell *shell);
t_lst		*make_list(t_env *envp);
t_lst		*duplicate_env(t_lst *env);
void		insert_last(t_lst **lst, t_lst *new);
t_lst		*insert_front(t_lst *new, char *var, char *msg, int type);

// exit.c
void		free_list(t_lst *list);
void		free_shell(t_shell shell);
void		get_exit_code(t_shell *shell);
void		free_table(t_cmd_table *cmd_table);
int			c_exit(t_shell *shell, t_cmd_table *cmd_table);

// export.c
void		sort_export(t_lst *env);
int			c_export(t_shell *shell, t_cmd_table *cmd_table);
void		print_export(t_lst *env);
int			add_export(t_shell *shell, char *var, char	*msg);
void		get_args(t_shell *shell, t_cmd_table *cmd_table); // mudar de local

// free.c
void		free_lex(t_lex *lex);
void		free_env(t_env *list);
void		free_join(t_shell *shell);
void		free_array(char ***token);
void		free_double(char ****array);

// handling.c
char		*get_name(void);
char		*make_text(void);
int			make_shell(t_shell *shell);
void		inicialize(t_shell *shell);
void		verify_builtins(t_shell *shell, t_cmd_table *cmd_table);

// lexer.c
char		***malloc_lexer(int size);
char		***make_lexer(t_lex *list);
void		insert_last_lex(t_lex **lst, t_lex *new);
t_lex		*insert_front_lex(t_lex *new, char *token, char *type);

// make_builtins.c
void		join_flag(t_shell *shell, int i);
void		join_content(t_shell *shell, int i);
char		*get_line(t_cmd_table *cmd_table, int cmd_index);
int			call_builtins(t_cmd_table *cmd_table, char *line, int cmd_index);
void		make_builtins(t_shell *shell, t_cmd_table *cmd_table);

// node.c
t_lst		*get_min(t_lst *env);
t_lst		*remove_min(t_lst *list, char *var);
void		add_node(t_shell shell, t_lst *node, t_lst *new_node);

// strcmp.c
int			strcmp_mod(const char *s1, const char *s2);
int			strcmp_rev(const char *s1, const char *s2);
int			strcmp_order(const char *s1, const char *s2);

// strtrim_mod.c
size_t		init(char *s1, char *set);
size_t		final(char *s1, char *set);
char		*strtrim_mod(char *s1, char *set);

// token.c
char		*id_token(char *token, int *has_content, int *has_echo);
int			lexer_size(t_lex *lexer);
char		***tokenization(t_shell *shell);
void		copy_token(char **token, t_lex **lex);
void		copy_list(char ***lex, t_lex *list, int size);

// tranfer_env.c
t_env		*tranfer_env(t_lst *env);
void		insert_last_env(t_env **lst, t_env *new);
t_env		*insert_front_env(t_env *new, char *var, char *msg, int type);

// unset.c
int			c_unset(t_shell *shell, t_cmd_table *cmd_table);
int			exe_unset(t_shell *shell);
void		verify_expansion(char **token);

// utils.c
int			isalnum_mod(char *c);
int			isdigit_mod(char *c);
char		*strchr_mod(const char *str, int c);
char		*strchr_rev(const char *str, int c);

// var.c
char		*put_final_sign(char *str);
char		*get_var(char *token, t_shell *shell);
char		*apart_var(t_shell *shell, char *token);

// verify.c
int			check_void(char *str, int i);
int			verify_commands(char *token);
int			verify_exceptions(char *token);
int			verify_list(char *token, char **list);

#endif
