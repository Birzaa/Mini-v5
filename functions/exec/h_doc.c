/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:30:06 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 11:05:33 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_h_r_in(t_redir_in_2 *r_in, int index)
{
	while (r_in)
	{
		if (r_in->h_doc)
		{
			r_in->file = NULL;
			index++;
		}
		r_in = r_in->next;
	}
	return (index);
}

char	*error_hdoc_name(t_pipex *pipex, char *name_file)
{
	ft_free_tab(pipex->h_doc_name);
	free(name_file);
	return (NULL);
}

char	*create_dest_file(t_pipex *pipex, int index, char *av)
{
	char	*index_str;
	char	*name_file;
	char	*dest_file;
	char	*idx;
	int		i;

	index_str = ft_itoa(index);
	name_file = ft_strjoin(av, index_str);
	free(index_str);
	dest_file = "/tmp";
	dest_file = ft_strjoin("/tmp/", name_file);
	pipex->h_doc_name[index] = ft_strdup(dest_file);
	if (!pipex->h_doc_name[index])
		if (!error_hdoc_name(pipex, name_file))
			return (NULL);
	i = 0;
	while (!access(dest_file, F_OK))
	{
		idx = ft_itoa(i);
		dest_file = ft_strjoin(pipex->h_doc_name[index], idx);
		free(idx);
		i++;
	}
	free(name_file);
	return (dest_file);
}

char	*hdoc_signal(int file, t_pipex *pipex)
{
	printf("\n");
	close(file);
	pipex->need_free = 1;
	pipex->need_exec = 1;
	dup2(pipex->saved_in, STDIN_FILENO);
	return (NULL);
}

void	reading_hdoc(int file, t_pipex *pipex, t_data *data, char *av)
{
	char	*buf;

	while (1)
	{
		buf = readline(BLUE "~> " RESET);
		if (!buf)
		{
			if (g_sig.status == 130)
				hdoc_signal(file, pipex);
			printf("bash: warning: here-document at line \
%d delimited by end-of-file (wanted `%s')\n", data->nb_input, av);
			break ;
		}
		if (!ft_strcmp(av, buf))
		{
			free(buf);
			break ;
		}
		(write(file, buf, ft_strlen(buf)), write(file, "\n", 1), free(buf));
	}
}
