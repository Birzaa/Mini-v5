/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:32:29 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/18 23:35:48 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_number_of_flags(t_cmd_word *cmd)
{
	int			count;
	t_cmd_word	*current;

	count = 0;
	current = cmd;
	while (current)
	{
		if (current->type == WORD)
		{
			count++;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		while (current->type == WHITE_SPACE && current->next)
			current = current->next;
		if (current->type != WORD)
			break ;
	}
	return (count);
}

int	put_word_in_tab(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd, int i)
{
	if (cmd->type == WORD)
	{
		parsed_cmd->full_cmd[i] = malloc(strlen(cmd->content) + 1);
		if (!parsed_cmd->full_cmd[i])
		{
			ft_free_tab(parsed_cmd->full_cmd);
			return (i);
		}
		strcpy(parsed_cmd->full_cmd[i], cmd->content);
		i++;
	}
	return (i);
}

void	parse_word(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd)
{
	int	i;

	i = 0;
	parsed_cmd->full_cmd = malloc(sizeof(char *) * (get_number_of_flags(cmd)
				+ 1));
	if (!parsed_cmd->full_cmd)
	{
		free(parsed_cmd->full_cmd);
		return ;
	}
	while (cmd)
	{
		while (cmd->type == WHITE_SPACE && cmd->next)
			cmd = cmd->next;
		if (cmd->type != WORD)
			break ;
		i = put_word_in_tab(cmd, parsed_cmd, i);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	parsed_cmd->full_cmd[i] = NULL;
}
