/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:32:29 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/13 13:18:42 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(t_cmd_word **cmd)
{
	if (is_redir((*cmd)->type) && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while ((*cmd)->type == WHITE_SPACE && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	else
		return (1);
	return (0);
}

void	get_number_of_flags(t_cmd_word *cmd, t_data *data)
{
	t_cmd_word	*current;

	current = cmd;
	while (current)
	{
		if (current->type == WORD && current->need_split)
		{
			if (skip_one_node(&current, data, 1))
				break ;
		}
		else if (current->type == WORD && skip_one_node(&current, data, 0))
		{
			break ;
		}
		while (current->type == WHITE_SPACE && current->next)
			current = current->next;
		while (current && is_redir(current->type))
		{
			skip(&current);
			while (current->type == WHITE_SPACE && current->next)
				current = current->next;
		}
		if (current->type != WORD)
			break ;
	}
}

int	put_word_in_tab_bis(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd, int i)
{
	int		j;
	char	**r;

	r = NULL;
	j = 0;
	r = ft_split(cmd->content, ' ');
	while (r[j])
	{
		parsed_cmd->full_cmd[i] = malloc(ft_strlen(r[j]) + 1);
		if (!parsed_cmd->full_cmd[i])
		{
			ft_free_tab(parsed_cmd->full_cmd);
			return (i);
		}
		parsed_cmd->nb_cmd++;
		ft_strcpy(parsed_cmd->full_cmd[i], r[j]);
		i++;
		j++;
	}
	ft_free_tab(r);
	return (i);
}

int	put_word_in_tab(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd, int i)
{
	if (cmd->type == WORD && cmd->need_split)
	{
		return (put_word_in_tab_bis(cmd, parsed_cmd, i));
	}
	else if (cmd->type == WORD)
	{
		parsed_cmd->full_cmd[i] = malloc(strlen(cmd->content) + 1);
		if (!parsed_cmd->full_cmd[i])
		{
			ft_free_tab(parsed_cmd->full_cmd);
			return (i);
		}
		parsed_cmd->nb_cmd++;
		strcpy(parsed_cmd->full_cmd[i], cmd->content);
		i++;
	}
	return (i);
}

void	parse_word(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd, t_data *data)
{
	int	i;

	i = 0;
	get_number_of_flags(cmd, data);
	parsed_cmd->full_cmd = malloc(sizeof(char *) * (data->count + 1));
	if (!parsed_cmd->full_cmd)
		return (free(parsed_cmd->full_cmd));
	while (cmd)
	{
		skip_space(&cmd);
		while (cmd && is_redir(cmd->type))
		{
			if (skip(&cmd))
			{
				parsed_cmd->full_cmd[i] = NULL;
				return ;
			}
			skip_space(&cmd);
		}
		if (cmd->type != WORD)
			break ;
		i = put_word_in_tab(cmd, parsed_cmd, i);
		cmd = cmd->next;
	}
	parsed_cmd->full_cmd[i] = NULL;
}
