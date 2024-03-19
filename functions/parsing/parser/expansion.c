/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/18 21:39:07 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_comb(char *content)
{
	int		len;
	int		i;
	char	**tab;

	len = 0;
	tab = NULL;
	i = 0;
	len = ft_strlen(content);
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = malloc((i + 2) * sizeof(char));
		if (!tab[i])
		{
			ft_free_tab(tab);
			return (NULL);
		}
		ft_strncpy(tab[i], content, i + 1);
		tab[i][i + 1] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_check_expand_exist(t_env *env, char *str)
{
	t_env	*tmp;
	int		len_c;
	char	*name_env;
	int		check;
	(void)check;
	check = 0;
	if (!str)
		return (0);
	if (ft_at_least_charset(str, "="))
		check = 1;
	len_c = ft_strlen(str);
	tmp = env;
	while (tmp)
	{
		name_env = ft_get_name_env(tmp->content);
		if (!ft_strncmp(name_env, str, len_c))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_get_expand_test(char *content, t_env *env)
{
	t_env	*tmp;
	int		len_c;
	char	*name_env;

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

int	ft_check_symbol(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isalnum(content[i]))
			return (1);
		i++;
	}
	return (0);
}

void	expand(t_cmd_word *cmd, t_data *data)
{
	char	*tmp;
	int		check;

	check = 0;
	(void)data;
	(void)check;
	cmd = cmd->next;
	printf("%s\n", cmd->content);
	printf("%d\n", check);
	if (ft_check_symbol(cmd->content) && cmd->state != IN_QUOTE)
		check = 1;
	if (!ft_check_expand_exist(data->env, cmd->content) && !check)
		return ;
	/* else if (check_combn(data->env, cmd->content))
	{
		// l'envoyer dans le get expand
	} */
	tmp = ft_get_expand_test(cmd->content, data->env);
	cmd->content = tmp;
	return ;
}

void	parsing_expand(t_cmd *cmd, t_data *data)
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
/* ft_check_comb_env(t_env *env, char **comb, char *content)
{

	(void)env;
	(void)comb;
	(void)content;
	return ;
} */
/* int	check_combn(t_env *env, char *content)
{
	comb = NULL;
	i = 0;
	(void)i;
	(void)env;
	comb = get_all_comb(content);
	if (!comb)
		return (0);
	else if (ft_check_comb_env(env, comb, content))
	{
		return (ft_free_tab(comb), 1);
	}
	return (ft_free_tab(comb), 0);
} */