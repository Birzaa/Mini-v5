/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:57 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/05 14:02:59 by abougrai         ###   ########.fr       */
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

void	exec_here_doc(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		g_sig.status = 130;
		close(STDIN_FILENO);
		return ;
	}
}

void	exec_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_sig.status = 131;
		g_sig.sigint = 1;
		g_sig.sigquit = 1;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_sig.status = 130;
		g_sig.sigint = 1;
		g_sig.sigquit = 1;
	}
}

void	handle_signal(int sig)
{
	if (!g_sig.pid)
		exec_signal(sig);
	else if (g_sig.pid == 2)
		exec_here_doc(sig);
	else
		minishell_signal(sig);
}

void	init_signals(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 1;
	g_sig.here_doc = 0;
	g_sig.input = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
