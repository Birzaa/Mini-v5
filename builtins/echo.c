/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:21 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/30 15:59:42 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **content, t_pipex *p)
{
	int	i;
	int	flag;
	(void)p;

	i = 1;
	flag = 0;
	if (!content[i])
		return (ft_putstr_fd("\n", 1));
	while (!ft_strncmp(content[i], "-n", 3))
	{
		flag = 1;
		i++;
		if (!content[i])
			break ;
	}
	while (content[i])
	{
		// printf("%s\n",content[i]);
		ft_putstr_fd(content[i++], 1);
		if (content[i])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	g_sig.status = 0;
}
