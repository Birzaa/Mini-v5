#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*cwd;

	(void)data;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(""));
	else if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		free(cwd);
		// g_ret_value = 0;
	}
}
