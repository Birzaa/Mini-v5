/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:41 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/25 21:00:31 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free tout ce qu'il y a a free
void	ft_exit(t_data *data)
{
	free_env(data->env);
	free_lexer(data->lex);
	free_parser(data->cmd, data->parsed_cmd);
	exit(0);
}
