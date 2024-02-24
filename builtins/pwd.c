#include "minishell.h"

/* void	ft_pwd(char **tab_command, t_shell *shell)
{
	char	*cwd;

	if (ft_strcmp(tab_command[0], "pwd") == 0 || ft_strcmp(tab_command[0],
			"\"pwd\"") == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			if (shell->fd)
			{
				printf("%s\n", cwd);
				close(shell->fd);
				dup2(shell->saved_stdout, STDOUT_FILENO);
			}
			else
				printf("%s\n", cwd);
			free(cwd);
		}
	}
} */
