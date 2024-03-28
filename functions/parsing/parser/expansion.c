/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/28 15:21:33 by thomas           ###   ########.fr       */
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

	tmp_join = ft_get_symbol_join(cmd->content);
	tmp_expand = ft_get_symbol_expand(cmd->content);
	if (!tmp_expand)
	{
		if (tmp_join)
			cmd->content = tmp_join;
		return (0);
	}
	tmp_full = ft_expand_symbol_bis(env, cmd, tmp_expand);
	if (!tmp_full && !tmp_join)
	{
		cmd->content = "";
		return (free(tmp_expand), 1);
	}
	else if (!tmp_full && tmp_join)
	{
		cmd->content = tmp_join;
		return (free(tmp_expand), 1);
	}
	cmd->content = ft_strcpy(cmd->content, tmp_full);
	return (free(tmp_full), free(tmp_expand), 0);
}

int	ft_expand_exist(t_env *env, t_cmd_word *cmd, int *expanded)
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
		if (!ft_strncmp(tmp->content, cmd->content, len_c) && len_var == len_c
			&& !check_value_env(tmp->content))
			cmd->content = "";
		else if (!ft_strncmp(tmp->content, cmd->content, len_c)
			&& len_var == len_c)
		{
			cmd->content = &tmp->content[len_var + 1];
			(*expanded) = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	expand(t_cmd_word *cmd, t_data *data)
{
	int	check;
	int	expanded;

	expanded = 0;
	check = 0;
	cmd = cmd->next;
	if (ft_check_symbol(cmd->content) && cmd->state != IN_QUOTE)
		check = 1;
	if (!ft_expand_exist(data->env, cmd, &expanded) && !check)
	{
		cmd->type = WHITE_SPACE;
		cmd->content = "";
		return ;
	}
	if (!expanded)
		ft_expand_symbol(data->env, cmd);
}

void	parsing_expand(t_cmd *cmd, t_data *data)
{
	t_cmd		*head;
	t_cmd_word	*tmp_word;
	int			check;

	head = cmd;
	while (head)
	{
		check = 0;
		tmp_word = head->words;
		while (tmp_word)
		{
			expand_check_next(tmp_word);
			expand_check_letter(tmp_word, &check);
			expand_check_quote(tmp_word);
			expand_check_expand(data, tmp_word, &check);
			expand_check_word(tmp_word);
			expand_continue(tmp_word, &check);
			if (!tmp_word->next)
				break ;
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
