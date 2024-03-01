/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_scnd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:35 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/01 23:19:58 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_close_dup(int last_file_descriptor, char **fileNames)
{
	close(last_file_descriptor);
	ft_free_tab(fileNames);
}

void	create_all_file(char **fileNames, int fileCount, t_cmd *shell,
		int d_redir)
{
	int	j;
	int		file_descriptor;
	int		last_file_descriptor;

	shell->saved_stdout = dup(STDOUT_FILENO);
	j = 0;
	while (j < fileCount - 1)
	{
		file_descriptor = open(fileNames[j], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (file_descriptor == -1)
			ft_free_tab(fileNames);
		close(file_descriptor);
		j++;
	}
	if (d_redir)
		last_file_descriptor = open(fileNames[fileCount - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		last_file_descriptor = open(fileNames[fileCount - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (last_file_descriptor == -1)
		ft_free_tab(fileNames);
	shell->fd = dup(STDOUT_FILENO);
	if (dup2(last_file_descriptor, STDOUT_FILENO) == -1)
		error_close_dup(last_file_descriptor, fileNames);
	ft_free_tab(fileNames);
}
