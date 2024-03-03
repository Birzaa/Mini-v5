/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:22:58 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/03 15:07:38 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_tab_file(t_redir_in *r_in, t_cmd *cmd)
{
	int	i;

	i = 0;
	r_in->tab = malloc(sizeof(char *) * (r_in->size));
	if (!r_in->tab)
		return ;
	while (cmd && cmd->words)
	{
		while (cmd->words && cmd->words->type == WHITE_SPACE)
			cmd->words = cmd->words->next;
		if (cmd->words && cmd->words->type == REDIR_IN)
		{
			cmd->words = cmd->words->next;
			while (cmd->words && cmd->words->type == WHITE_SPACE)
				cmd->words = cmd->words->next;
			if (cmd->words && cmd->words->type == WORD)
			{
				r_in->tab[i] = ft_strdup(cmd->words->content);
				i++;
			}
		}
		else
			break ;
		if (cmd->words && cmd->words->next)
			cmd->words = cmd->words->next;
		else
			break ;
	}
}
void	number_redir_in(t_cmd *cmd, t_redir_in *r_in)
{
	t_cmd_word	*current_word;

	r_in->size = 0;
	current_word = cmd->words;
	while (current_word)
	{
		while (current_word && current_word->type == WHITE_SPACE)
			current_word = current_word->next;
		if (current_word && current_word->type == REDIR_IN)
		{
			current_word = current_word->next;
			while (current_word && current_word->type == WHITE_SPACE)
				current_word = current_word->next;
			if (current_word && current_word->type == WORD)
				r_in->size++;
		}
		else
			break ;
		if (current_word && current_word->next)
			current_word = current_word->next;
		else
			break ;
	}
	if (r_in->size)
		put_in_tab_file(r_in, cmd);
}

void	open_redir_in(t_redir_in *r_in)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	while (i < r_in->size)
	{
		fd = open(r_in->tab[i], O_RDONLY, 0644);
		if (fd == -1)
		{
			perror("Erreur lors de l'ouverture du fichier de redirection IN");
			// A MODIFIER
		}
		else if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Erreur lors de la redirection de l'entrée standard");
			// MODIFIER
		}
		close(fd);
		i++;
	}
}
