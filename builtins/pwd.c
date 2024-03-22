/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:34 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:43:35 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*cwd;

	(void)data;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(""));
	else if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		free(cwd);
		g_sig.status = 0;
	}
}
