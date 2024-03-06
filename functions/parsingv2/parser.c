/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/06 02:21:26 by abougrai         ###   ########.fr       */
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

/*
	ETAPES :
	1) Esquiver espaces
	2) Si cest une reddirection => parse redir
	3) Si cest un mot suivit ou non dun flag => parse cmd
	4) Voir si ya une redirection out => redir out
	5) Si on rencontre un | nvlle commande
 */

void	parse(t_cmd *cmd)
{
	t_command	*command;
	t_command	*head;
	t_command	*tmp;
	int			i;
	int			k;
	int			j;

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
				parse_r_in(cmd->words, &command->parsed_cmd->r_in, 0);
			else if (cmd->words->type == HERE_DOC)
				parse_r_in(cmd->words, &command->parsed_cmd->r_in, 1);
			else if (cmd->words->type == REDIR_OUT)
				parse_r_out(cmd->words, &command->parsed_cmd->r_out, 0);
			else if (cmd->words->type == DREDIR_OUT)
				parse_r_out(cmd->words, &command->parsed_cmd->r_out, 1);
			/*  else if (cmd->words->type == WORD)
				parse_word(); */
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
	
	int fdp = 0;
	command->nb_command = i;
	while (fdp < command->nb_command  )
	{
		printf("Commande [%d]:\n",fdp);
		while (head->parsed_cmd->r_in)
		{
			printf("int[%d] : %s, is H_doc : %d\n", k++,
				head->parsed_cmd->r_in->file, head->parsed_cmd->r_in->h_doc);
			head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
		}
		while (head->parsed_cmd->r_out)
		{
			printf("out[%d] : %s\n", j++, head->parsed_cmd->r_out->file);
			head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
		}
		fdp++;
		head = head->next;
	}
}
