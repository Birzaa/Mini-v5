/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:13:29 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/07 19:13:56 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_out	*ft_redir_out_last(t_redir_out *redir)
{
	while (redir)
	{
		if (!redir->next)
			return (redir);
		redir = redir->next;
	}
	return (redir);
}

t_redir_out	*ft_redir_out_new(char *content, int append)
{
	t_redir_out	*elem;

	elem = malloc(sizeof(t_redir_out));
	if (!elem)
		return (NULL);
	elem->file = content;
	elem->append = append;
	elem->next = NULL;
	return (elem);
}

void	add_back_redir_out(t_redir_out **redir, t_redir_out *new)
{
	t_redir_out	*last;

	if (!*redir)
		*redir = new;
	else
	{
		last = ft_redir_out_last(*redir);
		last->next = new;
	}
}

void	parse_r_out(t_cmd_word *cmd, t_redir_out **r_out, int append)
{
	t_redir_out	*tmp;

	cmd = cmd->next;
	while (cmd->type == WHITE_SPACE)
		cmd = cmd->next;
	if (cmd->type == WORD)
	{
		tmp = ft_redir_out_new(cmd->content, append);
		if (!tmp)
			return ;
		add_back_redir_out(r_out, tmp);
	}
	return ;
}
