/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/05 22:06:17 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_command *list)
{
	list = ft_calloc(sizeof(t_command), 1);
	if (!list)
		return (NULL);
	list->nb_command = 0;
	list->parsed_cmd = NULL;
	return (list);
}

/*
	ETAPES :
	1) Esquiver espaces
	2) Si cest une reddirection => parse redir
	3) Si cest un mot suivit ou non dun flag => parse cmd
	4) Voir si ya une redirection out => redir out
	5) Si on rencontre un | nvlle commande
 */

void	parse(t_cmd *cmd)
{
	t_command	*command;
	int			i;

	command = NULL;
	i = 0;
	command = init_command(command);
	while (cmd)
	{
		if (!command)
			return ;
		while (cmd->words)
		{
			if (cmd->words->type == REDIR_IN)
			{
				parse_r_in(cmd->words);
				// printf("%s\n",command->parsed_cmd->r_in->file);
			}
			cmd->words = cmd->words->next;
		}
		command->nb_command++;
		i++;
		cmd = cmd->next;
	}
}
