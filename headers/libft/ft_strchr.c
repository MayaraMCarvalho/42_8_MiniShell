/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:08:02 by macarval          #+#    #+#             */
/*   Updated: 2023/05/04 16:10:48 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
				return ((char *)str);
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (0);
}
