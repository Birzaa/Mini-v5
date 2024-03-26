/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/26 14:05:11 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_node *info, t_cmd **head, t_cmd_word *new_word)
{
	t_cmd_word	*current;

	new_word->content = malloc(info->len + 1);
	ft_strncpy(new_word->content, info->content, info->len);
	new_word->content[info->len] = '\0';
	new_word->type = info->type;
	new_word->state = info->state;
	new_word->index = info->index;
	new_word->next = NULL;
	if ((*head)->words == NULL)
	{
		(*head)->words = new_word;
	}
	else
	{
		current = (*head)->words;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_word;
	}
}

void	add_cmd_cmd(t_node *info, t_cmd **head)
{
	t_cmd_word	*new_word;
	t_cmd		*new_cmd;

	if (*head == NULL)
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
		{
			return ;
		}
		new_cmd->words = NULL;
		new_cmd->next = NULL;
		*head = new_cmd;
	}
	new_word = malloc(sizeof(t_cmd_word));
	if (!new_word)
	{
		return ;
	}
	add_node(info, head, new_word);
}

void	not_a_pipe(t_cmd **current_cmd, t_cmd **new_cmd, t_cmd **cmd,
		t_node **current_node)
{
	if (!(*current_cmd))
	{
		(*new_cmd) = malloc(sizeof(t_cmd));
		if (!(*new_cmd))
		{
			return ;
		}
		(*new_cmd)->words = NULL;
		(*new_cmd)->next = NULL;
		(*current_cmd) = (*new_cmd);
		if (!(*cmd))
		{
			(*cmd) = (*current_cmd);
		}
	}
	add_cmd_cmd(*current_node, (current_cmd));
}

void	is_a_pipe(t_cmd **new_cmd, t_cmd **current_cmd, t_cmd **cmd)
{
	(*new_cmd) = malloc(sizeof(t_cmd));
	if (!(*new_cmd))
	{
		return ;
	}
	(*new_cmd)->words = NULL;
	(*new_cmd)->next = NULL;
	if (!(*cmd))
		(*cmd) = (*new_cmd);
	if ((*current_cmd))
		(*current_cmd)->next = (*new_cmd);
	(*current_cmd) = (*new_cmd);
}

t_cmd	*parser(t_stack *lst)
{
	t_cmd	*cmd;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;
	t_node	*current_node;

	new_cmd = NULL;
	cmd = NULL;
	current_cmd = NULL;
	current_node = lst->head;
	while (current_node)
	{
		if (current_node->type != PIPE_LINE)
		{
			not_a_pipe(&current_cmd, &new_cmd, &cmd, &current_node);
		}
		else
		{
			is_a_pipe(&new_cmd, &current_cmd, &cmd);
		}
		current_node = current_node->next;
	}
	return (cmd);
}
