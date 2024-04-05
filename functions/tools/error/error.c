/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:43 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/04 19:04:02 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *s1, char *s2)
{
	ft_putstr("bash: ");
	ft_putstr(s1);
	ft_putstr(": ");
	ft_putstr(s2);
	ft_putstr("\n");
}
