/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoferre <leoferre@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:03:43 by leoferre          #+#    #+#             */
/*   Updated: 2023/10/13 20:03:46 by leoferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_with_char(char const *s1, char const *s2, char c)
{
	int		i;
	int		j;
	size_t	total_len;
	char	*new_str;

	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)ft_malloc(total_len * sizeof(char) + 2);
	if (!new_str)
		return (NULL);
	while (s1[i++])
		new_str[i - 1] = s1[i - 1];
	new_str[i - 1] = c;
	while (s2[j++])
		new_str[i++] = s2[j - 1];
	new_str[i] = '\0';
	return (new_str);
}
