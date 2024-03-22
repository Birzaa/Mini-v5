/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/22 02:24:44 by abougrai         ###   ########.fr       */
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

	printf("test 8 : on effectue l'expand symbol \n\n\n");
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
		printf("test 7 : si env value exist pas");
		printf("type devient space content devien rien et on retrn \n");
		return ;
	}
	if (!expanded)
		ft_expand_symbol(data->env, cmd);
}
// if next est null

void	expand_check_letter(t_cmd_word *tmp_word, int *check)
{
	(void)check;
	if (tmp_word->type == ENV && (first_letter(tmp_word->next->content))
		&& ft_strncmp(tmp_word->next->content, "_", 2)
		&& tmp_word->next->state != 0)
	{
		printf("test2 : si actual == env et que premiere lettre next node\n");
		printf("Autre que quote || dquote || _\n");
		printf("env devient un mot et on avance\n");
		tmp_word->type = WORD;
		tmp_word = tmp_word->next;
		/* 	if (tmp_word->next && tmp_word->next->type != WHITE_SPACE)
			{
				printf("test3 : je sais pas pk on avance et check devient 1 \n\n\n");
				(*check) = 1;
			} */
	}
}

void	expand_check_quote(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && tmp_word->next
		&& (tmp_word->next->type == QOUTE
			|| tmp_word->next->type == DOUBLE_QUOTE) && tmp_word->state != 0)
	{
		printf("test4 : si actual = ENV et que next = quote || dquote\n");
		printf("on change le content en rien\n\n\n");
		tmp_word->content = "";
	}
}

void	expand_check_expand(t_data *data, t_cmd_word *tmp_word, int *check)
{
	if (tmp_word->type == ENV && tmp_word->state != 1 && tmp_word->next)
	{
		printf("test5 : si actual == env et que state different de 1 on veut expand\n");
		printf("$ devient whitespace\n");
		tmp_word->type = WHITE_SPACE;
		if (tmp_word->type == ENV && tmp_word->state == 2
			&& tmp_word->next->type == DOUBLE_QUOTE)
			tmp_word->type = WORD;
		if (check)
		{
			printf("test 6 : si check = 1 alors on est normalement dans un cas d'expand infini\n");
			printf("actual $ devient un word, je sais plus pk\n");
			tmp_word->type = WORD;
		}
		printf("dans tous les cas, content devient rien \n");
		tmp_word->content = "";
		expand(tmp_word, data);
		if (tmp_word->next)
			tmp_word = tmp_word->next;
		(*check) = 1;
		printf("test 9 : on avance si possible et check devient 1 car on peut rentrer dans un cas d'expand infini \n\n\n");
	}
}
void	expand_check_word(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && (!tmp_word->next || tmp_word->state == 1
			|| tmp_word->next))
	{
		printf("test 10 : si actual = env et que next null $ devient mot\n");
		printf("ou state = ' $ devient mot\n");
		printf("ou next non null $ devient mot\n\n\n");
		tmp_word->type = WORD;
	}
}

void	expand_check_next(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && (!tmp_word->next || tmp_word->state == 0))
	{
		if (!tmp_word->next)
		{
			tmp_word->type = WORD;
			return;
		}
		if (tmp_word->next->type == DOUBLE_QUOTE && tmp_word->state == 0)
			tmp_word->type = WORD;
		printf("test1 : si actual env et next null\n");
		printf("on avance pas\n");
		printf("ENV DEVIENT UN MOT\n\n\n");
	}
}

void	expand_continue(t_cmd_word *tmp_word, int *check)
{
	if (tmp_word->next && tmp_word->next->type == ENV && *check)
	{
		(*check) = 1;
		tmp_word = tmp_word->next;
		printf("last test : on est censer continue car expand infini\n\n\n");
	}
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
		printf("debut boucle : %d\n", check);
		tmp_word = head->words;
		while (tmp_word)
		{
			printf("%d\n", check);
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
