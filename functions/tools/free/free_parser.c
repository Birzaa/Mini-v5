/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:23:48 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 08:54:49 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_word(t_cmd_word *word)
{
	if (word)
	{
		if ((word->content))
			free(word->content);
		free(word);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd		*current_cmd;
	t_cmd		*next_cmd;
	t_cmd_word	*current_word;
	t_cmd_word	*next_word;

	current_cmd = cmd;
	while (current_cmd)
	{
		current_word = current_cmd->words;
		while (current_word)
		{
			next_word = current_word->next;
			free_cmd_word(current_word);
			current_word = next_word;
		}
		next_cmd = current_cmd->next;
		free(current_cmd);
		current_cmd = next_cmd;
	}
}

void	free_parser(t_cmd *head, t_command *command)
{
	if (command)
		free_command(command);
	if (head)
		free_cmd(head);
}
