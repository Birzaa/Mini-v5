#include "minishell.h"

void	ft_pwd(t_cmd *shell)
{
	char	*cwd;


	cwd = NULL;
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
