/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:33:56 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/06 21:25:15 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tmp_expand_null(t_cmd_word *cmd, char *tmp_expand, char *tmp_join)
{
	if (!tmp_expand)
	{
		if (tmp_join)
		{
			free(cmd->content);
			cmd->content = tmp_join;
			free(tmp_join);
		}
		return (1);
	}
	return (0);
}

int	full_and_join_null(t_cmd_word *cmd, char *tmp_expand, char *tmp_join,
		char *tmp_full)
{
	if (!tmp_full && !tmp_join)
	{
		free(cmd->content);
		cmd->content = ft_strdup("");
		return (free(tmp_expand), 1);
	}
	return (0);
}
