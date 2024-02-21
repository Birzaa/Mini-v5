/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:41 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 13:48:08 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_node *node);

void	print_list(t_stack *list)
{
	t_node	*node;
	int		i;

	i = 0;
	node = list->head;
	while (i < list->size)
	{
		print_node(node);
		node = node->next;
		i++;
	}
}

void	print_node(t_node *node)
{
	int	i;

	i = 0;
	printf("content: ");
	while (i < node->len)
		putchar(node->content[i++]);
	printf(", len: %i", node->len);
	printf(", state: %i", node->state);
	printf(", token: %i\n", node->type);
}
