/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_scnd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:35 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/01 18:22:45 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_size(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}

void	error_close_dup(int last_file_descriptor, char **fileNames,
		size_t fileCount)
{
	close(last_file_descriptor);
	free_tab_size(fileNames, fileCount);
}

void	create_all_file(char **fileNames, size_t fileCount, t_cmd *shell,
		int d_redir)
{
	size_t	j;
	int		file_descriptor;
	int		last_file_descriptor;

	shell->saved_stdout = dup(STDOUT_FILENO);
	j = 0;
	while (j < fileCount - 1)
	{
		if (d_redir == 1)
			file_descriptor = open(fileNames[j], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			file_descriptor = open(fileNames[j], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (file_descriptor == -1)
			free_tab_size(fileNames, fileCount);
		close(file_descriptor);
		j++;
	}
	if (d_redir == 1)
		last_file_descriptor = open(fileNames[fileCount - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		last_file_descriptor = open(fileNames[fileCount - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (last_file_descriptor == -1)
		free_tab_size(fileNames, fileCount);
	shell->fd = dup(STDOUT_FILENO);
	if (dup2(last_file_descriptor, STDOUT_FILENO) == -1)
		error_close_dup(last_file_descriptor, fileNames, fileCount);
	free_tab_size(fileNames, fileCount);
}

char	*ft_stuck(char *command, t_redir *redir, char *output_file, int d_redir)
{
	(void)d_redir;
	redir->len = 0;
	while (command[redir->i + 1] == ' ' || command[redir->i + 1] == '\t'
		|| command[redir->i] == '>')
	{
		redir->i++;
	}
	printf("c : %c\n",command[redir->i]);
	printf("c + 1 : %c\n",command[redir->i+1]);
	output_file = command + redir->i + 1;
	while (command[redir->i + 1] != ' ' && command[redir->i + 1] != '\t'
		&& command[redir->i + 1] != '\0')
	{
		(redir->i)++;
		(redir->len)++;
	}
	return (output_file);
}

void	put_in_tab_filename(char **fileNames, t_redir *redir, char *fileName)
{
	if (redir->len > 0)
	{
		fileName[redir->len] = '\0';
		fileNames[redir->current_file] = fileName;
		redir->current_file++;
		redir->len = 0;
	}
}
