/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:39 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 08:54:34 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	if (node)
		free(node);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = NULL;
	next = NULL;
	current = stack->head;
	if (current->content && !current->no_free)
		free(current->content);
	while (current)
	{
		if (current->status_free)
			free(current->content);
		next = current->next;
		free_node(current);
		current = next;
	}
	free(stack);
}

void	free_lexer(t_stack *stack)
{
	free_stack(stack);
}
