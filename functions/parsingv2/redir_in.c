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

t_redir_in_2	*ft_redir_in_2_last(t_redir_in_2 *redir)
{
	while (redir)
	{
		if (!redir->next)
			return (redir);
		redir = redir->next;
	}
	return (redir);
}

t_redir_in_2	*ft_redir_in_2_new(char *content, int h_doc)
{
	t_redir_in_2	*elem;

	elem = malloc(sizeof(t_redir_in_2));
	if (!elem)
		return (NULL);
	elem->file = content;
	// printf("%s\n",elem->file)
	elem->h_doc = h_doc;
	elem->next = NULL;
	return (elem);
}
void	add_back_redir(t_redir_in_2 **redir, t_redir_in_2 *new)
{
	t_redir_in_2	*last;

	if (!*redir)
		*redir = new;
	else
	{
		last = ft_redir_in_2_last(*redir);
		last->next = new;
	}
}

void	parse_r_in(t_cmd_word *cmd, t_redir_in_2 **r_in, int h_doc)
{
	t_redir_in_2	*tmp;

	cmd = cmd->next;
	while (cmd->type == WHITE_SPACE)
		cmd = cmd->next;
	if (cmd->type == WORD)
	{
		tmp = ft_redir_in_2_new(cmd->content, h_doc);
		if (!tmp)
			return ;
		add_back_redir(r_in, tmp);
			cmd = cmd->next;
	}
	return ;
}
