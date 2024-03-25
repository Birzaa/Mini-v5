/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:16 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/25 03:57:48 by abougrai         ###   ########.fr       */
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
		return (free(tmp_expand), 0);
	}
	else if (!tmp_full && tmp_join)
	{
		printf("test\n");
		cmd->content = tmp_join;
		return (free(tmp_expand), 1);
	}
	cmd->content = ft_strcpy(cmd->content, tmp_full);
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
			cmd->content = &tmp->content[len_var + 1];
			return (1);
		}
		tmp = tmp->next;
	}
	cmd->content = "";
	return (0);
}

void	expand(t_cmd_word *cmd, t_data *data)
{
	int			check;
	int			expanded;
	t_cmd_word	*tmp;

	tmp = cmd;
	expanded = 0;
	check = 0;
	cmd = cmd->next;
	printf("content : %s\n", cmd->content);
	if (ft_check_symbol(cmd->content) && cmd->state != IN_QUOTE)
		check = 1;
	printf("content : %d\n", check);
	if (!ft_expand_exist(data->env, cmd) && !check)
	{
		printf("go\n");
		cmd->type = WHITE_SPACE;
		cmd->content = "";
		tmp->type = WHITE_SPACE;
		tmp->content = "";
		return ;
	}
	if (!expanded && !check)
		tmp->content = "$";
	if (expanded && !check)
	{
		printf("test 2\n");
		tmp->content = "";
	}
	if (!expanded)
	{
		print_test();
		if (!ft_expand_symbol(data->env, cmd))
		{
			if (cmd->next && cmd->next->state == 2 && cmd->content)
			{
				printf("test 5\n");
				printf("%s\n", cmd->next->content);
				printf("%s\n", cmd->next->content);
				printf("%s\n", tmp->content);
				tmp->content = "";
			}
			else if (cmd->next && tmp->next->state == 0 && !cmd->content)
			{
				printf("test 6\n");
				tmp->content = "$";
			}
			else
				tmp->content = "";
		}
	}
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
			word->content = &tmp->content[len_var + 1];
			return (1);
		}
		tmp = tmp->next;
	}
	word->content = "";
	word->type = WHITE_SPACE;
	return (0);
}

int	first_step(t_cmd_word *cmd, t_data *data)
{
	t_cmd_word	*env;
	t_cmd_word	*word;
	int			symbol;
	int			expanded;

	env = cmd;
	word = cmd->next;
	symbol = ft_check_symbol(word->content);
	if (ft_strncmp(word->content, "_", 2) && first_letter(word->content))
	{
		env->type = WORD;
	}
	else if (ft_strncmp(word->content, "_", 2) && symbol)
	{
		expanded = ft_expand_symbol(data->env, word);
		if (expanded && !env->state)
			env->content = "";
		printf("test yes\n");
		printf("new content : %s\n", word->content);
		return (1);
	}
	else if (!symbol)
	{
		expanded = ft_expand_no_symbol(data->env, word);
		if (!expanded)
		{
			env->state = 2;
			if (!env->state)
				env->state = 2;
			printf("test2\n");
		}
		else
		{
			printf("test5\n");
			env->content = "";
		}
		printf("test no\n");
		printf("new content : [%s]\n", word->content);
		return (1);
	}
	printf("no expand\n");
	printf("new content : %s\n", word->content);
	return (0);
}

void	parsing_expand(t_cmd *cmd, t_data *data)
{
	t_cmd		*head;
	t_cmd_word	*tmp_word;
	int			expanded;

	(void)cmd;
	(void)data;
	(void)expanded;
	head = cmd;
	while (head)
	{
		tmp_word = head->words;
		while (tmp_word)
		{
			expanded = 0;
			if (tmp_word->type == ENV && tmp_word->next
				&& tmp_word->next->type == WORD && tmp_word->state != 1)
			{
				tmp_word->type = WHITE_SPACE;
				expanded = first_step(tmp_word, data);
				tmp_word = tmp_word->next;
			}
			else if (tmp_word->type == ENV && (tmp_word->state == 1
					|| tmp_word->next->type == DOUBLE_QUOTE
					|| tmp_word->next->type == QOUTE
					|| tmp_word->next->type == WHITE_SPACE))
			{
				print_test();
				tmp_word->type = WORD;
			}
			if (tmp_word->next && tmp_word->next->type == ENV && expanded)
			{
				tmp_word = tmp_word->next;
				printf("infini\n");
				continue ;
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}

/* void	parsing_expand(t_cmd *cmd, t_data *data)
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
} */