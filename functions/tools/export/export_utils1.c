/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:45:19 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_export(t_env **env, char *content)
{
	t_env	*tmp;
	int		len_n;
	int		len_tmp;
	int		check;

	len_tmp = 0;
	check = 0;
	if (ft_at_least_charset(content, "="))
		check = 1;
	len_n = get_len_to_equal(content);
	tmp = (*env);
	while (tmp)
	{
		len_tmp = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, content, len_n) && len_tmp == len_n)
		{
			if (!check && ft_at_least_charset(tmp->content, "="))
				return ;
			else if (check)
				tmp->content = content;
		}
		tmp = tmp->next;
	}
}

int	export_exist(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;

	if (!content)
		return (1);
	len_c = get_len_to_equal(content);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, content, len_c + 2))
		{
			printf("test 4\n");
			printf("%d\n", len_c);
			if (ft_strncmp(tmp->content, content, ft_strlen(content)))
			{
				printf("test 5\n");
				tmp->content = content;
				return (1);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	exp_exist_bis(t_env *env, char *content)
{
	t_env	*tmp;

	if (!content)
		return (1);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, content, 50))
		{
			tmp->content = content;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_export(char *content)
{
	int	i;

	i = 0;
	if (!ft_strncmp("_=", content, 2))
		return ;
	else if (!ft_at_least_charset(content, "="))
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(content, 1);
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_putstr_fd("export ", 1);
	while (content[i] != '=')
		write(1, &content[i++], 1);
	write(1, &content[i++], 1);
	write(1, "\"", 1);
	while (content[i])
		write(1, &content[i++], 1);
	write(1, "\"\n", 2);
}

int	ft_export_checking(char *content)
{
	int	i;

	i = 0;
	if (!isalpha(content[i]) && !ft_charcmp(content[i], '_'))
		return (1);
	return (0);
}
