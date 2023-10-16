#include "../../headers/token.h"
#include "../../headers/error.h"
#include "../../headers/expansions.h"

int	handle_quotes(char *str, char **temp, t_cmd_table *cmd_table)
{
	char	*text;
	char	*temporary;
	char	quote;
	int		str_i;

	str_i = 0;
	text = ft_malloc(1 * sizeof(char));
	text[0] = '\0';
	while (str[str_i] == '\'' || str[str_i] == '"')
	{
		quote = str[str_i];
		temporary = get_quote_text(&str[str_i], cmd_table);
		if (!temporary)
			return (free(text), -1);
		text = ft_strjoin_free(text, temporary);
		str_i++;
		while (str[str_i] != quote)
			str_i++;
		str_i++;
	}
	*temp = text;
	return (str_i);
}

void	create_io_file_tokens(t_token **head)
{
	t_token	*i;

	i = *head;
	while (i != NULL)
	{
		if (i->type == REDIRECT && i->next != NULL)
		{
			if (!ft_strncmp(i->text, ">>", 2) && i->next != NULL)
				i->next->type = APPEND;
			else if (!ft_strncmp(i->text, "<<", 2) && i->next != NULL)
				i->next->type = DELIMITER;
			else if (!ft_strncmp(i->text, "<", 1) && i->next != NULL)
				i->next->type = INFILE;
			else if (!ft_strncmp(i->text, ">", 1) && i->next != NULL)
				i->next->type = OUTFILE;
		}
		i = i->next;
	}
}

int	create_redirection_token(char *str, t_cmd_table *cmd_table)
{
	char	*text;
	int		i;

	i = 0;
	while (str[i] && !ft_iswhitespace(str[i]))
	{
		if ((str[i] != '>' && str[i] != '<') || i >= 2)
			break ;
		i++;
	}
	text = ft_substr(str, 0, i);
	create_token(REDIRECT, text, cmd_table);
	return (i);
}

int	create_word_token(char *str, char **temp)
{
	char	*text;
	int		i;

	i = 0;
	while (str[i] && !ft_iswhitespace(str[i]) && !ismetachar(str[i]))
		i++;
	text = ft_substr(str, 0, i);
	*temp = text;
	return (i);
}
