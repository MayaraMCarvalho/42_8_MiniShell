/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:26:28 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:52:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	quantity_words(const char *str, char c)
{
	size_t	len;

	if (!str || !str[0])
		return (0);
	while (*str && *str == c)
		str++;
	len = counter(str, c);
	return (len);
}

int	counter(const char *str, char c)
{
	int		control;
	size_t	len;

	control = 0;
	len = 0;
	while (*str)
	{
		if (*str != c)
		{
			if (quotes_close(str) > 0)
				str += verify_quotes(str);
			if (control == 0)
			{
				control = 1;
				len++;
			}
		}
		else if (*str == c)
			control = 0;
		str++;
	}
	return (len);
}

size_t	len_word(const char *str, char c, size_t len)
{
	size_t	tam;
	char	quote;
	int		control;

	if (!str)
		return (1);
	tam = 0;
	control = quotes_close(str);
	while (str[len] != c && str[len])
	{
		if (control > 0 && (str[len] == '\'' || str[len] == '"'))
		{
			quote = str[len];
			if (!str[len + 1] || str[len + 1] == quote)
				return (0);
			len++;
			while (str[len++] && str[len] != quote)
				tam++;
			tam += 2;
		}
		tam++;
		len++;
	}
	return (tam);
}

char	*copy_word(const char *s, char c, size_t len)
{
	size_t	j;
	size_t	i;
	char	*str;

	j = 0;
	i = len_word(s, c, len);
	str = malloc ((i + 1) * sizeof(char));
	if (!str || i == 0)
	{
		free(str);
		return (NULL);
	}
	while (j < i)
	{
		str[j] = s[len + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split_mod(char const *s, char c)
{
	size_t	j;
	size_t	len;
	char	**str;
	size_t	words;

	j = 0;
	len = 0;
	words = quantity_words(s, c);
	str = (char **) malloc ((words + 1) * sizeof(char *));
	if (!str || words == 0)
	{
		free(str);
		return (NULL);
	}
	while (j < words)
	{
		while (s[len] == c && s[len])
			len++;
		str[j] = copy_word(s, c, len);
		j++;
		len += len_word(s, c, len);
	}
	str[j] = 0;
	return (str);
}
