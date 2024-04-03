/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:15 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/03 12:28:22 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redir(enum e_token type)
{
	if (type == REDIR_IN)
		return ("`<'");
	if (type == REDIR_OUT)
		return ("`>'");
	if (type == HERE_DOC)
		return ("`<'");
	if (type == DREDIR_OUT)
		return ("`>'");
	return (".");
}

t_node	*check_unclosed_quotes(t_node **node, enum e_token type)
{
	while (*node)
	{
		*node = (*node)->next;
		if (!*node || (*node)->type == type)
			break ;
	}
	if (!*node)
	{
		g_sig.status = 2;
		write(STDERR_FILENO, "minishell: unclosed quotes detected.\n",
			ft_strlen("minishell: unclosed quotes detected.\n"));
	}
	return (*node);
}

int	error_cmd2(t_stack *lst, t_node *node)
{
	if (lst->size == 1 && node->type == PIPE_LINE)
	{
		g_sig.status = 2;
		return (ft_perror("minishell: syntax error near \
unexpected token `|'",
							NULL));
	}
	return (EXIT_SUCCESS);
}

int	error_cmd(t_stack *lst)
{
	t_node	*node;

	node = lst->head;
	if (error_cmd2(lst, node))
		return (EXIT_FAILURE);
	while (node)
	{
		if (node->type == PIPE_LINE)
		{
			if (is_invalid_pipe(node))
				return (ft_perror("minishell: syntax error near \
unexpected token `|'",
									NULL));
		}
		else if (is_redir(node->type))
		{
			if (is_invalid_redir(node))
				return (ft_perror("minishell: syntax error near \
unexpected token ",
									get_redir(node->type)));
		}
		else if (node->type == DOUBLE_QUOTE || node->type == QOUTE)
			if (!check_unclosed_quotes(&node, node->type))
				return (EXIT_FAILURE);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
