/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:43 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/06 13:22:54 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *s1, char *s2)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}
void	handle_error_cd(char *s1, char *s2)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_error_export(char *s1)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd("not a valid identifier\n",2);
}