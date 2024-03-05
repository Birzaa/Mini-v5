/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/05 19:06:06 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 0;
	while (cmd)
	{
		command = malloc(sizeof(t_command));
		if (!command)
			return ;
		while (cmd->words)
		{
			if (cmd->words->type == REDIR_IN)
				parse_r_in(cmd->words);
			cmd->words = cmd->words->next;
		}
		command = command->next;
		i++;
		cmd = cmd->next;
	}
}
