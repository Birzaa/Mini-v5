#include "minishell.h"

void	ft_cd_tild(char *command, t_data *data)
{
}

void	ft_cd_home(t_data *data)
{
	char	*home;

	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return ;
		if (chdir(&home[5]))
			printf("cd: %s: No such file or directory\n", &home[5]);
		free(home);
		// g_ret_value = 0;
	}
	else
		printf("bash: home is not set\n");
	// g_ret_value = 1;
}

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

char	*ft_getenv(t_env *env, char *n)
{
	t_env	*tmp;
	char	*content;
	int		len_n;

	content = NULL;
	tmp = env;
	len_n = ft_strlen(n);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, n, len_n))
		{
			content = ft_strdup(tmp->content);
			if (!content)
				return (NULL);
			return (content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_cd(char *command, t_data *data)
{
	char	*home;

	home = NULL;
	(void)home;
	refresh_env(data->env, 1);
	if (!ft_strncmp(command, "~", 1))
		ft_cd_home(data);
	else if (!ft_at_least_charset(command, '~'))
		ft_cd_tild(data, command);
	// home = ft_is_home_set(data->env);
	if (chdir(command) != 0)
		printf("cd: %s: No such file or directory\n", command);
}
