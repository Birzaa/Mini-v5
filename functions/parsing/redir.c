/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:58:35 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/02 17:06:18 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_cmd_word *cmd, t_redir_list *redir)
{
	char	*content;

	while (cmd->type != WORD && cmd->type != ENV)
		cmd = cmd->next;
	content = ft_strdup(cmd->content);
	add_redir_last(redir, new_redir_node(content, cmd->type,
			ft_strlen(content)));
}

t_redir_list	*parsing_redir(t_cmd *cmd)
{
	t_redir_list	*redir;
	t_cmd_word		*current_word;

	redir = NULL;
	redir = init_redir_list(redir);
	if (!redir)
		return (NULL);
	current_word = cmd->words;
	while (current_word && current_word->type != PIPE_LINE)
	{
		if (is_redir(current_word->type))
			parse_redir(current_word, redir);
		current_word = current_word->next;
	}
	return (redir);
}
