/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:26:15 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/09 17:38:24 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*skip_spaces(t_node *ptr, int opt)
{
	while (ptr && (ptr->type == WHITE_SPACE || ptr->type == QOUTE
			|| ptr->type == DOUBLE_QUOTE))
	{
		if (opt)
			ptr = ptr->prev;
		else
			ptr = ptr->next;
	}
	return (ptr);
}

int	is_redir(enum e_token type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == DREDIR_OUT
		|| type == HERE_DOC);
}

int	is_invalid_pipe(t_node *node)
{
	t_node	*prev;

	prev = node;
	if (node->type == PIPE_LINE)
	{
		if (!prev->prev)
			return (EXIT_FAILURE);
		if (prev->prev)
			prev = prev->prev;
		else
			return (EXIT_FAILURE);
		while (prev && (prev->type == WHITE_SPACE || prev->type == QOUTE
				|| prev->type == DOUBLE_QUOTE || prev->type == ENV))
			prev = prev->prev;
		if (prev->type != WORD)
			return (EXIT_FAILURE);
		if (!node->next)
			return (EXIT_FAILURE);
		node = node->next;
		while (node->next && (node->type == WHITE_SPACE || node->type == QOUTE
				|| node->type == DOUBLE_QUOTE || is_redir(node->type)
				|| node->type == ENV))
			node = node->next;
		if (node->type != WORD)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_perror(char *str, char *option)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	if (option)
		write(STDERR_FILENO, option, ft_strlen(option));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

int	is_invalid_redir(t_node *node)
{
	t_node	*next;

	next = skip_spaces(node->next, 0);
	if (!next || ((next->type != WORD && next->type == DOUBLE_QUOTE
				&& next->type == QOUTE) && next->type != ENV))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
