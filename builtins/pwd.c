#include "minishell.h"

void	ft_pwd(t_cmd *shell)
{
	(void)shell;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}
