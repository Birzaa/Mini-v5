/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/01 06:50:03 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_symbol_bis(t_env *env, t_cmd_word *cmd, char *tmp_expand)
{
	t_env	*tmp;
	char	*tmp_join;
	char	*full;
	int		len_var;
	int		len_expand;

	tmp = env;
	full = NULL;
	tmp_join = ft_get_symbol_join(cmd->content);
	len_expand = ft_strlen(tmp_expand);
	while (tmp)
	{
		len_var = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, tmp_expand, len_expand)
			&& len_var == len_expand)
		{
			full = ft_strjoin(&tmp->content[len_var + 1], tmp_join);
			if (!full)
				return (perror(""), NULL);
			return (full);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_expand_symbol(t_env *env, t_cmd_word *cmd)
{
	char	*tmp_expand;
	char	*tmp_full;
	char	*tmp_join;

	tmp_join = ft_strdup(ft_get_symbol_join(cmd->content));
	tmp_expand = ft_get_symbol_expand(cmd->content);
	if (!tmp_expand)
	{
		if (tmp_join)
		{
			free(cmd->content);
			cmd->content = tmp_join;
			free(tmp_join);
		}
		return (0);
	}
	tmp_full = ft_expand_symbol_bis(env, cmd, tmp_expand);
	if (!tmp_full && !tmp_join)
	{
		free(cmd->content);
		cmd->content = ft_strdup("");
		return (free(tmp_expand), 0);
	}
	else if (!tmp_full && tmp_join)
	{
		free(cmd->content);
		cmd->content = ft_strdup(tmp_join);
		free(tmp_join);
		return (free(tmp_expand), 1);
	}
	if (tmp_join)
		free(tmp_join);
	free(cmd->content);
	cmd->content = ft_strdup(tmp_full);
	return (free(tmp_full), free(tmp_expand), 0);
}

int	ft_expand_exist(t_env *env, t_cmd_word *cmd)
{
	t_env	*tmp;
	int		len_c;
	int		len_var;

	if (!cmd->content)
		return (0);
	len_var = 0;
	len_c = ft_strlen(cmd->content);
	tmp = env;
	while (tmp)
	{
		len_var = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, cmd->content, len_c) && len_var == len_c)
		{
			free(cmd->content);
			cmd->content = ft_strdup(&tmp->content[len_var + 1]);
			return (1);
		}
		tmp = tmp->next;
	}
	free(cmd->content);
	cmd->content = ft_strdup("");
	return (0);
}

int	ft_expand_no_symbol(t_env *env, t_cmd_word *word)
{
	t_env	*tmp;
	int		len_c;
	int		len_var;

	if (!word->content)
		return (0);
	len_var = 0;
	len_c = ft_strlen(word->content);
	tmp = env;
	while (tmp)
	{
		len_var = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, word->content, len_c) && len_var == len_c)
		{
			free(word->content);
			word->content = ft_strdup(&tmp->content[len_var + 1]);
			return (1);
		}
		tmp = tmp->next;
	}
	free(word->content);
	word->content = ft_strdup("");
	word->type = WHITE_SPACE;
	return (0);
}

void	parsing_expand(t_cmd *cmd, t_data *data)
{
	t_cmd *head;
	t_cmd_word *tmp_word;

	head = cmd;
	while (head)
	{
		tmp_word = head->words;
		while (tmp_word)
		{
			while_expand(data, tmp_word);
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}