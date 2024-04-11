/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:10:33 by thomas            #+#    #+#             */
/*   Updated: 2024/04/11 06:08:34 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_expand(t_cmd_word *actual, t_cmd_word *next)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(actual->content, next->content);
	if (!tmp)
		return ;
	next->content = ft_strcpy(next->content, tmp);
	free(tmp);
	actual->content = " ";
}

/* void	del_node_env(t_env *target, t_env *previous)
{
	if (!target->next)
	{
		previous->next = NULL;
		free(target);
	}
	else
	{
		previous->next = target->next;
		free(target);
	}
} */
