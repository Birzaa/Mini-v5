/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:27 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/13 12:10:01 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, t_pipex *p, char **content)
{
	int	fd;

	fd = p->outfile;
	if (!content[1])
	{
		print_env(data->env, fd);
		g_sig.status = 0;
	}
	else if (content[1])
	{
		ft_putstr_fd("env: ", fd);
		ft_putstr_fd("‘", fd);
		ft_putstr_fd(content[1], fd);
		ft_putstr_fd("‘ ", fd);
		ft_putstr_fd("No such file or directory\n", fd);
		g_sig.status = 1;
	}
}
// ft_printf("env: ’%s’: No such file or directory\n", content[1]);
