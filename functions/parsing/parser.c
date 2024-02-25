/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/25 07:47:44 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list2(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (cmd)
	{
		printf("%s", temp->cmd);
		temp = temp->next;
	}
}

void	parser(t_stack *lst)
{
	t_cmd	*cmd;
	int		i;
	t_cmd	*next_cmd;
	t_cmd	*head;

	cmd = malloc(sizeof(t_cmd));
	cmd->node = lst->head;
	cmd->next = NULL;
	head = cmd;
	i = 0;
	while (i < lst->size && cmd->node)
	{
		printf(" node content : %s\n", cmd->node->content);
		printf("avant join : cmdcmd %s\n", cmd->cmd);
		cmd->cmd = ft_strjoin(cmd->node->content, " ");
		printf("apres join : cmdcmd %s\n\n", cmd->cmd);
		if (cmd->node->type == PIPE_LINE)
		{
			// printf("%s\n", cmd->cmd);
			next_cmd = malloc(sizeof(t_cmd));
			next_cmd->node = cmd->node->next;
			next_cmd->next = NULL;
			cmd->next = next_cmd;
			cmd = next_cmd;
		}
		cmd->node = cmd->node->next;
		i++;
	}
}

/* 	while (cmd)
	{
		printf("%s\n", cmd->content);
		cmd = cmd->next;
	}
}

t_cmd	*new_node_cmd(char *content)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_back_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!*cmd)
		*cmd = new;
	else
	{
		last = ft_cmd_last(*cmd);
		last->next = new;
	}
}

void	parser(t_stack *lex)
{
	t_node	*node;
	t_cmd	*cmd;
	char	*new_cmd;
	char	*new_cmd2;
	int		i;
	int		j;
	int		k;

	new_cmd = "";
	(void)cmd;
	i = 0;
	k = 0;
	node = lex->head;
	while (i < lex->size)
	{
		node = node->next;
		j = 0;
		new_cmd2 = malloc(sizeof(node->len));
		while (j < node->len)
		{
			new_cmd2[j] = node->content[k];
			printf("new : %c  contet : %c\n", new_cmd2[j], node->content[k]);
			k++;
			j++;
		}
		if (node->type == PIPE_LINE)
		{
			printf("final cmd : %s\n", new_cmd);
		}
		new_cmd2[j] = '\0';
		printf("cmd = %s\n", new_cmd2);
		new_cmd = ft_strjoin(new_cmd2, " ");
		free(new_cmd2);
		i++;
	}
	printf("\n\n\n");
}


/* void	parser(t_stack *lex)
{
	t_node	*node;
	t_cmd	*cmd;
	char	*new_cmd;
	char	**tab_cmd;
	int		i;

	i = 0;
	new_cmd = "";
	(void)cmd;
	node = lex->head;
	tab_cmd = ft_split(node->content, '|');
	while (tab_cmd[i])
	{
		printf("%s\n", tab_cmd[i++]);
	}
	printf("\n\n\n");
}*/

// cmd1 | cmd2 | cmd3
