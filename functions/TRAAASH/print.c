/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:41 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/08 18:24:21 by thenwood         ###   ########.fr       */
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
	printf(", token: %i\n", node->type);
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

//<infile <<eof wc -l > outfile | ls -llllll | ls -a -a -a | ls $HOME > fichier | ls >>finalfile
