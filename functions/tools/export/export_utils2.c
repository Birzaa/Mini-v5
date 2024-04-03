/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:30:22 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/03 12:42:55 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)env;
	(void)content;
	return (0);
}

void	handle_replace_export(t_env *tmp, char *content)
{
	if (tmp->exported)
		free(tmp->content);
	tmp->exported = 1;
	tmp->content = ft_strdup(content);
}
