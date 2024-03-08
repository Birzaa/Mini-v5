/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/08 18:48:39 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_env_exist_test(char *content, t_env *env)
{
	t_env	*tmp;
	int		len_c;
	char	*temp;
	char	*name_env;

	temp = NULL;
	if (!content)
		return (0);
	len_c = ft_strlen(content);
	tmp = env;
	while (tmp)
	{
		name_env = ft_get_name_env(tmp->content);
		if (!ft_strncmp(name_env, content, len_c))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_get_expand_test(char *content, t_env *env)
{
	t_env	*tmp;
	int		len_c;
	char	*temp;
	char	*name_env;

	temp = NULL;
	if (!content)
		return (0);
	len_c = ft_strlen(content);
	tmp = env;
	while (tmp)
	{
		name_env = ft_get_name_env(tmp->content);
		if (!ft_strncmp(name_env, content, len_c))
		{
			return (ft_strdup(&tmp->content[len_c + 1]));
		}
		tmp = tmp->next;
	}
	return (0);
}

void	remplacer_env(t_cmd_word *cmd, t_data *data)
{
	char	*tmp;

	cmd = cmd->next;
	if (!ft_check_env_exist_test(cmd->content, data->env))
		return ;
	tmp = ft_get_expand_test(cmd->content, data->env);
	cmd->content = tmp;
	return ;
}

void	expand(t_cmd_word *cmd, t_data *data)
{
	remplacer_env(cmd, data);
}

void	test_exp(t_cmd *cmd, t_data *data)
{
	t_cmd		*head;
	t_cmd_word	*tmp_word;

	head = cmd;
	while (head)
	{
		tmp_word = head->words;
		while (tmp_word)
		{
			if (tmp_word->type == ENV && tmp_word->state != 1)
			{
				tmp_word->type = WHITE_SPACE;
				tmp_word->content = " ";
				expand(tmp_word, data);
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
