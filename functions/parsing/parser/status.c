/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:58 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/05 09:58:14 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istoken(int c)
{
	if (c == WHITE_SPACE || c == NEW_LINE || c == QOUTE || c == ENV
		|| c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT
		|| c == DOUBLE_QUOTE || c == DREDIR_OUT || c == HERE_DOC)
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

void	change_status(t_node *node, char *wanted, char *status, char *tmp)
{
	wanted = ft_strcpy(wanted, node->next->content);
	tmp = ft_strjoin(status, &wanted[1]);
	if (!tmp)
		return (perror(""), free(status), free(wanted));
	wanted = ft_strcpy_status(wanted, tmp);
	node->type = WORD;
	node->content = "";
	node->no_free = 1;
	node->next->type = WORD;
	node->next->status_free = 1;
	node->next->content = wanted;
	node->next->no_free = 0;
	node->next->len = ft_strlen(wanted);
	free(tmp);
}

void	handle_status(t_node *node, char *status)
{
	char	*tmp;
	char	*wanted;
	int		i;

	i = 0;
	if (node->next->content)
		i = ft_strlen(node->next->content);
	(void)status;
	wanted = malloc(i + 8);
	if (!wanted)
		return ;
	tmp = NULL;
	if (!ft_strncmp(node->next->content, "?", 1))
		change_status(node, wanted, status, tmp);
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
				"?", 1) && node->state != 1)
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
