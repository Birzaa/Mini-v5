/* ************t_redir_elem************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:26:51 by thomas            #+#    #+#             */
/*   Updated: 2024/03/05 21:21:10 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_in_2	*new_r_node(char *content, int h_doc)
{
	t_redir_in_2	*elem;

	elem = ft_calloc(sizeof(t_redir_in_2), 1);
	if (!elem)
		return (NULL);
	elem->file = content;
	elem->h_doc = h_doc;
	elem->next = NULL;
	return (elem);
}

void add_r_last(t_redir_in_2 *list, t_redir_in_2 *new)
{
    if (!list->current)
    {
        list->next = new;
        list->current = new;
    }
    else
    {
        list->current->next = new;
        list->current = new;
    }
}




void	parse_r_in(t_cmd_word *cmd)
{
	t_redir_in_2	*r_in;

	r_in = ft_calloc(sizeof(t_redir_in_2), 1);
	if (!r_in)
		return ;
	cmd = cmd->next;
	while (cmd->type == WHITE_SPACE)
		cmd = cmd->next;
	if (cmd->type == WORD)
	{
		add_r_last(r_in, new_r_node(cmd->content, 0));
	}
	printf("%s\n",r_in->file);
}
