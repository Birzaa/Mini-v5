/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:58 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:44:34 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istoken(int c)
{
	if (c == WHITE_SPACE || c == NEW_LINE || c == QOUTE || c == ENV
		|| c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT)
		return (c);
	return (0);
}

char	*ft_strcpy_status(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] && !ft_istoken(s2[i]))
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	handle_status(t_node *node, char *status)
{
	char	*tmp;
	char	*content;

	tmp = NULL;
	content = NULL;
	if (!ft_strncmp(node->next->content, "?", 1))
	{
		content = ft_strchr(node->next->content, '?');
		tmp = ft_strjoin(status, ++content);
		if (!tmp)
			return (perror(""), free(status));
		node->type = WORD;
		node->content = "";
		node->next->type = WORD;
		node->next->content = ft_strcpy_status(node->next->content, tmp);
		node->next->len = ft_strlen(node->next->content);
	}
	return (free(tmp));
}

void	parsing_status(t_stack *list)
{
	char	*status;
	t_node	*node;
	int		i;

	i = 0;
	status = ft_itoa(g_sig.status);
	if (!status)
		return (perror(""));
	node = list->head;
	while (i < list->size)
	{
		if (node->type == ENV && node->next && !ft_strncmp(node->next->content,
				"?", 1))
			handle_status(node, status);
		if (!node->next)
		{
			free(status);
			break ;
		}
		node = node->next;
		i++;
	}
}
