#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# include "env_init.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_cmd_table	t_cmd_table;

typedef struct s_token		t_token;

typedef enum s_type {
	WORD,
	REDIRECT,
	PIPE,
	INFILE,
	OUTFILE,
	APPEND,
	DELIMITER,
}	t_type;

typedef struct s_token {
	t_type		type;
	char		*text;
	t_token		*next;
}	t_token;

int		tokenize_string(char *input_string, t_cmd_table *cmd_table);
int		assign_token(char *str, t_cmd_table *cmd_table);
void	create_token(t_type type, char *text, t_cmd_table *cmd_table);
void	create_io_file_tokens(t_token **head);
int		create_redirection_token(char *str, t_cmd_table *cmd_table);
int		create_word_token(char *str, char **temp);
int		handle_quotes(char *str, char **temp, t_cmd_table *cmd_table);
int		handle_words(char *str, t_cmd_table *cmd_table);
int		select_type(char *str, int str_i, char **temp, t_cmd_table *cmd_table);

int		count_cmd(t_token **head);
int		ft_iswhitespace(char a);
int		ismetachar(char a);
void	ft_lstadd_back(t_token **head, t_token *new);
t_token	*ft_lstnew(t_type type, char *text);
void	free_func_token(t_token **head);
int		is_valid_var_name_char(char a);

#endif
