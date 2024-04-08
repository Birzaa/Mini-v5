/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:14:04 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/08 17:00:34 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_command *list)
{
	list = ft_calloc(sizeof(t_command), 1);
	if (!list)
		return (NULL);
	list->nb_command = 0;
	list->current = NULL;
	list->head = NULL;
	list->parsed_cmd = NULL;
	list->next = NULL;
	return (list);
}

t_parsed_cmd	*init_redir(t_parsed_cmd *list)
{
	list = ft_calloc(sizeof(t_parsed_cmd), 1);
	if (!list)
		return (NULL);
	list->r_in = NULL;
	list->r_out = NULL;
	list->nb_cmd = 0;
	list->full_cmd = NULL;
	return (list);
}

t_command	*ft_command_last(t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

t_command	*ft_command_new(void)
{
	t_command	*elem;

	elem = malloc(sizeof(t_command));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->current = NULL;
	elem->head = NULL;
	elem->nb_command = 0;
	elem->parsed_cmd = NULL;
	return (elem);
}

void	add_back_cmd_out(t_command **cmd, t_command *new)
{
	t_command	*last;

	if (!*cmd)
		*cmd = new;
	else
	{
		last = ft_command_last(*cmd);
		last->next = new;
	}
}
