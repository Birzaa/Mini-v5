/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:30:22 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/06 23:26:55 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_real_export_name(char *content, char *cpy)
{
	int	i;

	i = 0;
	while (content[i] != '+')
	{
		cpy[i] = content[i];
		i++;
	}
	cpy[i++] = '=';
	cpy[i] = '\0';
	return (cpy);
}

int	ft_export_exist_for_add(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;
	int		len_tmp;

	len_tmp = 0;
	len_c = get_len_to_equal(content);
	tmp = env;
	while (tmp)
	{
		len_tmp = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, content, len_c) && len_tmp == len_c)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export_add_checking(char *cmd)
{
	int	i;
	int	operation;
	int	first_letter;

	i = 0;
	operation = 0;
	first_letter = 0;
	if (cmd[0] != '=' && cmd[0] != '+')
	{
		first_letter = 1;
		i = 1;
	}
	while (cmd[i])
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
		{
			operation = 1;
			break ;
		}
		i++;
	}
	if (first_letter && operation)
		return (1);
	return (0);
}

int	ft_export_op(t_env *env, char *content)
{
	char	*name;
	char	*value;
	char	*join;

	join = NULL;
	name = NULL;
	value = NULL;
	name = ft_strdup(content);
	if (!name)
		return (perror(""), 1);
	name = ft_get_real_export_name(content, name);
	value = ft_get_value_env(content);
	if (!value)
		return (free(name), 1);
	if (ft_export_exist_for_add(env, name))
	{
		if (ft_export_add_case_one(env, join, name, value))
			return (1);
	}
	else
	{
		if (ft_export_add_case_two(env, name, value))
			return (1);
	}
	return (free(name), free(value), 0);
}

void	handle_replace_export(t_env *tmp, char *content)
{
	if (tmp->exported)
		free(tmp->content);
	tmp->exported = 1;
	tmp->content = ft_strdup(content);
}
