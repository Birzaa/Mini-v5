/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:57 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/26 18:43:30 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_signal(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig.status = 130;
	}
}

void	exec_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_sig.sigquit = 1;
		g_sig.status = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_sig.sigint = 1;
		g_sig.status = 130;
	}
}

void	get_signal(int sig)
{
	printf("%d\n", sig);
	printf("%d\n", g_sig.pid);
	if (!g_sig.pid)
		exec_signal(sig);
	else
		minishell_signal(sig);
}

void	init_signals(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 1;
	g_sig.input = NULL;
	signal(SIGINT, get_signal);
	signal(SIGQUIT, get_signal);
}
