/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:03:14 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/30 14:18:02 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*malloc_lst(t_stack *stack)
{
	stack = ft_calloc(sizeof(t_stack), 1);
	if (!stack)
		return (NULL);
	return (stack);
}

t_node	*new_node(char *content, int len, enum e_token type, enum e_state state)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->len = len;
	new_node->type = type;
	new_node->state = state;
	new_node->no_free = 0;
	new_node->index = -1;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add_back(t_stack *lst, t_node *node)
{
	if (!lst->head)
		lst->head = node;
	else
	{
		lst->tail->next = node;
		node->prev = lst->tail;
	}
	lst->tail = node;
	lst->size++;
}
