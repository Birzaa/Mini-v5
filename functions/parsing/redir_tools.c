/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:03:37 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/01 21:54:25 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_list	*init_redir_list(t_redir_list *list)
{
	list = ft_calloc(sizeof(t_redir_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_redir_elem	*new_redir_node(char *content, enum e_token type, int len)
{
	t_redir_elem	*elem;

	elem = ft_calloc(sizeof(t_redir_elem), 1);
	if (!elem)
		return (NULL);
	elem->arg = content;
	elem->len = len;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	add_redir_last(t_redir_list *list, t_redir_elem *new)
{
	if (!list->head)
		list->head = new;
	else
		list->tail->next = new;
	list->tail = new;
	list->size++;
}

void	free_redir_list(t_redir_list *list)
{
	t_redir_elem	*tmp;

	tmp = list->head;
	while (tmp)
	{
		free(tmp->arg);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}

void	print_redir_list(t_redir_list *redir)
{
	t_redir_elem	*tmp;

	tmp = redir->head;
	while (tmp)
	{
		printf("redir type: %i\n", tmp->type);
		printf("redir arg: %s\n", tmp->arg);
		tmp = tmp->next;
		if (tmp)
			printf("\nNext :\n");
	}
}
