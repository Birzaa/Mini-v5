#include "minishell.h"

int	ft_is_home_set(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME", 4))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_cd(char *command, t_data *data)
{
	int	home;

	(void)home;
	home = 0;
	refresh_env(data->env, 1);
	home = ft_is_home_set(data->env);
	if (chdir(command) != 0)
		printf("cd: %s: No such file or directory\n", command);
}
