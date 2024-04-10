/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:41 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 08:52:25 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_node *node);

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] : %s", i, tab[i]);
		if (tab[i + 1])
			printf("  |  ");
		i++;
	}
}

void	print_list(t_stack *list)
{
	t_node	*node;
	int		i;

	i = 0;
	node = list->head;
	while (i < list->size)
	{
		print_node(node);
		node = node->next;
		i++;
	}
}

void	print_node(t_node *node)
{
	int	i;

	i = 0;
	printf("content: ");
	while (i < node->len)
		putchar(node->content[i++]);
	printf(", len: %i", node->len);
	printf(", state: %i", node->state);
	printf(", token: %i", node->type);
	printf(", index: %i\n", node->index);
}

void	print_parsed_cmd(t_command *head)
{
	int	fdp;
	int	k;
	int	j;
	int	r;

	k = 0;
	j = 0;
	fdp = 0;
	r = head->nb_command;
	while (fdp < r)
	{
		printf("----------------------------------\n");
		printf("Commande [%d]:\n\n", fdp);
		while (head->parsed_cmd->r_in)
		{
			printf("Redir in[%d] : '%s', is H_doc : %d\n", k++,
				head->parsed_cmd->r_in->file, head->parsed_cmd->r_in->h_doc);
			head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
		}
		printf("\n");
		while (head->parsed_cmd->r_out)
		{
			printf("Redir out[%d] : '%s', is D_R : %d\n", j++,
				head->parsed_cmd->r_out->file, head->parsed_cmd->r_out->append);
			head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
		}
		if (head->parsed_cmd->full_cmd)
		{
			printf("\n");
			printf("Full cmd : ");
			print_tab(head->parsed_cmd->full_cmd);
			printf("\n");
		}
		fdp++;
		head = head->next;
	}
}

void	print_cmd_list(t_cmd *head)
{
	t_cmd		*current;
	int			i;
	t_cmd_word	*word;

	current = head;
	i = 0;
	while (current)
	{
		word = current->words;
		printf("CMD[%d]:\n", i);
		while (word)
		{
			printf("Content: %s, Type: %d, State: %d\n", word->content,
				word->type, word->state);
			word = word->next;
		}
		i++;
		current = current->next;
		printf("\n");
	}
}

//<Makefile <<eof wc -l > outfile | ls -llllll | ls -a -a-a |echo "''Bonjour' 'tocard''" |ls $HOME > fichier | ls >>'"'c'"'
//<Makefile cat -e -e       -e | ls-alt |sleep 5 | sleep 10 | <<eof ls |<Makefile cat  >a>>b