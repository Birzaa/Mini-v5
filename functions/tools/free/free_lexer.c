/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:39 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/07 19:33:38 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	if (!node)
		return ;
	free(node->content);
	free(node);
}

void	free_stack(t_stack *stack)
{
	t_node	*tmp;

	if (!stack)
		return ;
	while (stack->head)
	{
		tmp = stack->head;
		stack->head = stack->head->next;
		free_node(tmp);
	}
	free(stack);
}

void	free_lexer(t_stack *stack)
{
	free_stack(stack);
}
