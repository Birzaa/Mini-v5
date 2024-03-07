#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	printf(ORANGE "\U0001F58A  ~>: " RESET);
}

void	ctrl_slash(int sig)
{
	(void)sig;
	/* 	if (g_sig.pid != 0)
		{
			kill(g_sig.pid, SIGQUIT);
		}
		else */
	printf(ORANGE "\U0001F58A  ~>: " RESET);
}

void	ctrl_d(int sig, t_data *data)
{
	(void)sig;
	(void)data;
	ft_exit(data);
}

void	init_signals(void)
{
	struct sigaction	sa;

	// Initialisation de la structure t_signal
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	// Configuration du gestionnaire de signal pour SIGINT (Ctrl+C)
	sa.sa_handler = ctrl_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	// Configuration du gestionnaire de signal pour SIGQUIT (Ctrl+\)
	sa.sa_handler = ctrl_slash;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	// Configuration du gestionnaire de signal pour SIGTERM (Ctrl+D)
	sa.sa_handler = (void (*)(int))ctrl_d;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGTERM, &sa, NULL);
}
