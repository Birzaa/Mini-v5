/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:23:48 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/24 16:58:02 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_word(t_cmd_word *word)
{
	if (word)
	{
		free(word->content);
		free(word);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd_word	*current_word;
	t_cmd_word	*next_word;

	current_word = cmd->words;
	while (current_word)
	{
		next_word = current_word->next;
		free_cmd_word(current_word);
		current_word = next_word;
	}
	free(cmd);
}

void	free_parser(t_cmd *head, t_command *command)
{
	if (command)
		free_command(command);
	if (head)
		free_cmd(head);
}
