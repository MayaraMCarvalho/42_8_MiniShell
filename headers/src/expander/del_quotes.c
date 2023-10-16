#include "../../headers/expansions.h"
#include "../../headers/token.h"
#include "../../headers/error.h"

char	*get_quote_text(char *str, t_cmd_table *cmd_table)
{
	char	*text;
	int		i;

	i = 1;
	while (str[i] != str[0] && str[i])
		i++;
	if (!str[i])
		return (NULL);
	text = ft_substr(str, 1, i - 1);
	if (str[0] == '"')
		text = expand_var_quotes(text, cmd_table);
	return (text);
}

char	*expand_var_quotes(char *text, t_cmd_table *cmd_table)
{
	char	*expanded_string;
	int		i;

	expanded_string = ft_malloc(1 * sizeof(char));
	expanded_string[0] = '\0';
	i = 0;
	while (text[i])
	{
		if (text[i] != '$' || (text[i] == '$' && !text[i + 1]))
			expanded_string = add_char(expanded_string, text, i);
		if ((text[i] == '$' && text[i + 1]))
			i += join_env_var(&text[i], &expanded_string, cmd_table);
		else
			i++;
	}
	free(text);
	return (expanded_string);
}

char	*add_char(char *exp_string, char *text, int i)
{
	char	*added_char;

	added_char = ft_substr(text, i, 1);
	exp_string = ft_strjoin_free(exp_string, added_char);
	return (exp_string);
}

int	join_env_var(char *str, char **expanded_string, t_cmd_table *cmd_table)
{
	char	*var_value;
	char	*var_name;
	int		var_name_len;

	var_name_len = get_var_name(str, &var_name);
	var_value = find_var_value(var_name, cmd_table);
	if (var_value)
		*expanded_string = ft_strjoin_free(*expanded_string, var_value);
	return (var_name_len);
}
