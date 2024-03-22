/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:27 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:52:26 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, char **content)
{
	if (!content[1])
	{
		print_env(data->env);
		g_sig.status = 0;
	}
	else if (content[1])
	{
		ft_printf("env: ’%s’: No such file or directory\n", content[1]);
		g_sig.status = 1;
	}
}
