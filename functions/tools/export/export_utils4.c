/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:19:53 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/11 12:44:27 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_add_case_one_bis(t_env *target, char *name, char *value,
		char *tmp)
{
	tmp = ft_strjoin(name, value);
	if (!tmp)
		return (free(name), free(value), 1);
	if (target->exported && target->content)
		free(target->content);
	target->content = tmp;
	target->exported = 1;
	return (free(name), free(value), 0);
}

int	ft_export_add_case_one(t_env *env, char *join, char *name, char *value)
{
	char	*tmp;
	t_env	*target;

	tmp = NULL;
	target = NULL;
	join = ft_export_join_content(env, name);
	target = ft_get_target_export(env, name);
	if (!ft_at_least_charset(join, "="))
	{
		if (ft_export_add_case_one_bis(target, name, value, tmp))
			return (1);
	}
	tmp = ft_strjoin(join, value);
	if (!tmp)
		return (free(name), free(value), 1);
	if (target->exported && target->content)
		free(target->content);
	target->content = tmp;
	target->exported = 1;
	return (0);
}

int	ft_export_add_case_two(t_env *env, char *name, char *value)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(name, value);
	if (!tmp)
		return (free(name), free(value), 1);
	export_new_add_back_add(&env, tmp);
	return (0);
}

void	ft_putstr_fd_before(char *s, int fd, char c)
{
	int	i;
	
	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ;
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putstr_fd_from(char *s, int fd, char c)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != c)
		i++;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
