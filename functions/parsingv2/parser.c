/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/06 16:47:17 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_command *list)
{
	list = ft_calloc(sizeof(t_command), 1);
	if (!list)
		return (NULL);
	list->nb_command = 0;
	list->parsed_cmd = NULL;
	list->next = NULL;
	return (list);
}

t_parsed_cmd	*init_redir(t_parsed_cmd *list)
{
	list = ft_calloc(sizeof(t_parsed_cmd), 1);
	if (!list)
		return (NULL);
	list->r_in = NULL;
	list->r_out = NULL;
	list->full_cmd = NULL;
	return (list);
}

void	skip_dr_out(t_cmd *cmd)
{
	if (cmd->words->type == DREDIR_OUT&& cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE&& cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
	// printf("content : %s\n", cmd->words->content);

}

void	skip_r_out(t_cmd *cmd)
{
	if (cmd->words->type == REDIR_OUT&& cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE&& cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
	// printf("content : %s\n", cmd->words->content);

}

void	skip_h_doc(t_cmd *cmd)
{
	if (cmd->words->type == HERE_DOC&& cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE&& cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
	// printf("content : %s\n", cmd->words->content);

}

void	skip_r_in(t_cmd *cmd)
{
	if (cmd->words->type == REDIR_IN&& cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE&& cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
	// printf("content : %s\n", cmd->words->content);

}

void	parse(t_cmd *cmd)
{
	t_command	*command;
	t_command	*head;
	t_command	*tmp;
	int			i;
	int			k;
	int			j;
	int			fdp;

	tmp = NULL;
	command = NULL;
	i = 0;
	command = init_command(command);
	head = command;
	while (cmd)
	{
		command->parsed_cmd = init_redir(command->parsed_cmd);
		if (!command)
			return ;
		while (cmd->words)
		{
			if (cmd->words->type == REDIR_IN)
			{
				parse_r_in(cmd->words, &command->parsed_cmd->r_in, 0);
				skip_r_in(cmd);
				// printf("content : %s\n", cmd->words->content);
			}
			else if (cmd->words->type == HERE_DOC)
			{
				parse_r_in(cmd->words, &command->parsed_cmd->r_in, 1);
				skip_h_doc(cmd);
				/* printf("content : %s\n",cmd->words->content); */
			}
			else if (cmd->words->type == REDIR_OUT)
			{
				parse_r_out(cmd->words, &command->parsed_cmd->r_out, 0);
				skip_r_out(cmd);
				/* printf("content : %s\n",cmd->words->content); */
			}
			else if (cmd->words->type == DREDIR_OUT)
			{
				parse_r_out(cmd->words, &command->parsed_cmd->r_out, 1);
				skip_dr_out(cmd);
				/* printf("content : %s\n",cmd->words->content); */
			}
			else if (cmd->words->type == WORD)
			{
				parse_word(cmd->words, command->parsed_cmd->full_cmd);
			}
			cmd->words = cmd->words->next;
		}
		tmp = ft_command_new();
		add_back_cmd_out(&command, tmp);
		command = command->next;
		command->nb_command++;
		head->nb_command++;
		i++;
		cmd = cmd->next;
	}
	k = 0;
	j = 0;
	fdp = 0;
	command->nb_command = i;
	while (fdp < command->nb_command)
	{
		printf("----------------------------------\n");
		printf("Commande [%d]:\n", fdp);
		while (head->parsed_cmd->r_in)
		{
			printf("Redir in[%d] : %s, is H_doc : %d\n", k++,
				head->parsed_cmd->r_in->file, head->parsed_cmd->r_in->h_doc);
			head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
		}
		while (head->parsed_cmd->r_out)
		{
			printf("Redir out[%d] : %s, is D_R : %d\n", j++, head->parsed_cmd->r_out->file, head->parsed_cmd->r_out->append);
			head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
		}
		if(head->parsed_cmd->full_cmd)
		{
			printf("Full cmd :\n");
			print_tab(head->parsed_cmd->full_cmd);
		}
		fdp++;
		head = head->next;
	}
}

//<infile <<eof wc -l > outfile | ls -llllll | ls -a -a -a | ls >>finalfile
