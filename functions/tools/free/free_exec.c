/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:14:05 by thomas            #+#    #+#             */
/*   Updated: 2024/03/27 18:47:47 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->h_doc_name)
		{
			ft_free_tab(pipex->h_doc_name);
		}
	}
}
