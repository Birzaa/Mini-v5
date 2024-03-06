/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:32:29 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/06 16:46:26 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_number_of_flags(t_cmd_word *cmd)
{
	int		count;
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

void	parse_word(t_cmd_word *cmd, char **tab)
{
	int	i;

	i = 0;
	tab = malloc(sizeof(char *) * (get_number_of_flags(cmd) + 1));
	if (!tab)
	{
		free(tab);
		return ;
	}
	while (cmd)
	{
		if (cmd->type != WHITE_SPACE && cmd->type != WORD)
			break ;
		if (cmd->type == WORD)
		{
			tab[i] = malloc(sizeof(ft_strlen(cmd->content)));
			if (!tab[i])
			{
				ft_free_tab(tab);
				return ;
			}
			tab[i] = cmd->content;
			i++;
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break;
	}
	tab[i] = NULL;
}
