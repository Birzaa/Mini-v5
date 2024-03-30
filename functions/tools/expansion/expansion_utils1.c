/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:44:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/30 12:11:41 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_symbol(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isalnum(content[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_symbol_join(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
			return ((content + i));
		i++;
	}
	return (NULL);
}

char	*ft_get_symbol_expand(char *content)
{
	char	*expand;
	int		i;

	i = 0;
	expand = ft_calloc(1, ft_strlen_symbol(content) + 2);
	if (!expand)
		return (NULL);
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
		{
			return (expand);
		}
		expand[i] = content[i];
		i++;
	}
	free(expand);
	return (NULL);
}


int	ft_strlen_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	first_letter(char *content)
{
	if (!content)
		return (0);
	if (ft_at_least_charset(content, "\'\""))
		return (0);
	if (!ft_isalpha(content[0]))
		return (1);
	return (0);
}
