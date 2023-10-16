#include "../../headers/token.h"
#include "../../headers/parser.h"
#include "../../headers/expansions.h"
#include "../../headers/error.h"

int	tokenize_string(char *input_string, t_cmd_table *cmd_table)
{
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	while (input_string[i])
	{
		if (input_string[i] && !ft_iswhitespace(input_string[i]))
		{
			temp = assign_token(&input_string[i], cmd_table);
			if (temp == -1)
				return (printf("bash: syntax error near unexpected token `\\n'\n"));
			i += temp;
		}
		else
			i++;
		if (i >= (int)ft_strlen(input_string))
			break ;
	}
	if (grammar_check(cmd_table->token_head, cmd_table))
		return (1);
	create_io_file_tokens(cmd_table->token_head);
	return (0);
}

int	assign_token(char *str, t_cmd_table *cmd_table)
{
	if (*str == '|')
		create_token(PIPE, ft_strdup("|"), cmd_table);
	else if (*str == '>' || *str == '<')
		return (create_redirection_token(str, cmd_table));
	else
		return (handle_words(str, cmd_table));
	return (1);
}

int	handle_words(char *str, t_cmd_table *cmd_table)
{
	char	*total_text;
	char	*temp;
	int		str_i;
	int		temp_str_i;

	total_text = ft_malloc(1 * sizeof(char));
	total_text[0] = '\0';
	str_i = 0;
	while (str[str_i] && !ft_iswhitespace(str[str_i]) && str[str_i] != '|'
		&& str[str_i] != '>' && str[str_i] != '<')
	{
		temp_str_i = select_type(str, str_i, &temp, cmd_table);
		if (temp_str_i == -1)
			return (free(total_text), -1);
		str_i += temp_str_i;
		if (temp)
			total_text = ft_strjoin_free(total_text, temp);
	}
	create_token(WORD, total_text, cmd_table);
	return (str_i);
}

int	select_type(char *str, int str_i, char **temp, t_cmd_table *cmd_table)
{
	int	temp_str_i;

	temp_str_i = 0;
	if (str[str_i] == '\'' || str[str_i] == '"')
		temp_str_i = handle_quotes(&str[str_i], temp, cmd_table);
	else if (str[str_i] == '$' && str[str_i + 1] == '?')
		temp_str_i = expand_exit_status(&str[str_i], temp, cmd_table);
	else if (str[str_i] == '$')
		temp_str_i = expand_env_var(&str[str_i], temp, cmd_table);
	else
		temp_str_i = create_word_token(&str[str_i], temp);
	return (temp_str_i);
}
