/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:11:24 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/01 17:20:17 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

size_t	count_files(char *command)
{
	int		i;
	size_t	file_count;

	i = 0;
	file_count = 0;
	while (command[i])
	{
		if (command[i] == '>')
		{
			while (command[i + 1] == ' ' || command[i + 1] == '\t')
				i++;
			while (command[i + 1] != ' ' && command[i + 1] != '\t' && command[i
				+ 1] != '\0')
			{
				i++;
			}
			file_count++;
		}
		i++;
	}
	return (file_count);
}

char	**malloc_tab(char **file_names, size_t fileCount)
{
	file_names = malloc(fileCount * sizeof(char *));
	if (!file_names)
	{
		free(file_names);
		return (NULL);
	}
	return (file_names);
}
void	create_file_redi(char *command, size_t fileCount, t_cmd *shell,
		int d_redir)
{
	char	**file_names;
	char	*file_name;
	char	*output_file;
	t_redir	redir;

	(void)d_redir;
	output_file = NULL;
	file_names = NULL;
	redir.i = 0;
	file_names = malloc_tab(file_names, fileCount);
	redir.current_file = 0;
	while (command[redir.i])
	{
		if (command[redir.i] == '>')
		{
			output_file = ft_stuck(command, &redir, output_file);
			file_name = malloc(redir.len + 1);
			if (!file_name)
				free_tab_size(file_names, fileCount);
			ft_strncpy(file_name, output_file, redir.len);
			put_in_tab_filename(file_names, &redir, file_name);
		}
		redir.i++;
	}
	create_all_file(file_names, fileCount, shell);
}

void	redirection_out(t_cmd *data)
{
	size_t		file_count;
	char		*cmd;
	t_cmd		*current;
	t_cmd_word	*word;
	int			d_redir;

	cmd = "";
	d_redir = 0;
	current = data;
	if (current)
	{
		word = current->words;
		while (word)
		{
			if (word->type == DREDIR_OUT)
				d_redir = 1;
			cmd = ft_strjoin(cmd, word->content);
			word = word->next;
		}
	}
	data->fd = 0;
	data->saved_stdout = 0;
	file_count = count_files(cmd);
	if (file_count)
		create_file_redi(cmd, file_count, data, d_redir);
}
