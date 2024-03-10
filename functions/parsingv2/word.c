/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:32:29 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/09 23:57:26 by abougrai         ###   ########.fr       */
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

int	len_word(t_cmd_word *cmd)
{
	int				len;
	enum e_state	state;

	len = 0;
	state = cmd->state;
	while (cmd)
	{
		if (cmd->state != state)
			break ;
		len += ft_strlen(cmd->content);
		cmd = cmd->next;
	}
	return (len);
}

int	put_word_in_tab(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd, int i)
{
	char	*str;
	enum e_state	state;
	state = cmd->state;

	str = "";
	if (cmd->type == WORD)
	{
		len_word(cmd);
		parsed_cmd->full_cmd[i] = malloc(len_word(cmd) + 1);
		if (!parsed_cmd->full_cmd[i])
		{
			ft_free_tab(parsed_cmd->full_cmd);
			return (i);
		}
		while (cmd)
		{
			str = ft_strjoin(str, cmd->content);
			if (cmd->state != state)
				break ;
			cmd = cmd->next;
		}
		// printf("str : %s\n",str);
		strcpy(parsed_cmd->full_cmd[i], str);
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
		while ((cmd->type == WHITE_SPACE || cmd->type == DOUBLE_QUOTE
				|| cmd->type == QOUTE) && cmd->next)
			cmd = cmd->next;
		if (cmd->type != WORD)
			break ;
		printf("pdt la bocle : %s\n", cmd->content);
		i = put_word_in_tab(cmd, parsed_cmd, i);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	parsed_cmd->full_cmd[i] = NULL;
}
