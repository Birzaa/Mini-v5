/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:22:55 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/12 20:58:21 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_charset(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	int		i;
	char	*new;

	if (!s1)
		return (NULL);
	start = 0;
	while (ft_charset(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (ft_charset(set, s1[end - 1]) && end > start)
		end--;
	new = malloc(sizeof(char) * (end - start) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (start < end)
		new[i++] = s1[start++];
	new[i] = '\0';
	return (new);
}
