/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:11:24 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/02 13:20:03 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_tab(char **file_names, int fileCount)
{
	file_names = malloc(fileCount * sizeof(char *));
	if (!file_names)
	{
		free(file_names);
		return (NULL);
	}
	return (file_names);
}
void	create_file_redi(char *command, int d_redir, t_cmd *shell,
		t_redir_list *redir_two)
{
	char	**file_names;
	char	*file_name;
	t_redir	redir;

	file_names = NULL;
	redir.i = 0;
	file_names = malloc_tab(file_names, redir_two->size);
	redir.current_file = 0;
	while (command[redir.i])
	{
		if (command[redir.i] == '>')
		{
			if (command[redir.i + 1] == '>')
				redir.i++;
			file_name = ft_strdup(redir_two->head->arg);
			if (!file_name)
				ft_free_tab(file_names);
			file_names[redir.current_file] = file_name;
			redir.current_file++;
			redir_two->head = redir_two->head->next;
			 if (!redir_two->head)
                break;
		}
		redir.i++;
	}
	create_all_file(file_names, redir_two->size, shell, d_redir);
	ft_free_tab(file_names);
}

void	redirection_out(t_cmd *data, t_redir_list *redir)
{
	char		*cmd;
	t_cmd		*current;
	t_cmd_word	*word;
	int			d_redir;

	d_redir = 0;
	cmd = "";
	current = data;
	if (current)
	{
		word = current->words;
		while (word)
		{
			if (word->type == DREDIR_OUT)
				d_redir = 1;
			else if (word->type == REDIR_OUT)
				d_redir = 0;
			cmd = ft_strjoin(cmd, word->content);
			word = word->next;
		}
	}
	data->fd = 0;
	data->saved_stdout = 0;
	if (redir->size)
		create_file_redi(cmd, d_redir, data, redir);
	free(cmd);
}
