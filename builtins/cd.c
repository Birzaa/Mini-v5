#include "minishell.h"

int	ft_more_than_one_char(char *str, char c)
{
	int	i;
	int	more;

	i = 0;
	more = 0;
	while (str[i])
	{
		if (str[i] == c)
			more++;
		else if (more > 1)
			return (1);
		i++;
	}
	return (0);
}
void	ft_cd_tild(char *command, t_data *data)
{
	char	*new_cmd;
	char	*tmp;
	char	*home;
	int		i;

	home = NULL;
	new_cmd = "";
	if (ft_more_than_one_char(command, '~'))
	{
		printf("bash: cd: %s: No such file or directory\n", command);
		return ;
		// g_ret_value = 1;
	}
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return ;
		i = 0;
		while (command[i])
		{
			if (command[i] == '~')
			{
				while (command[i] == '~')
				{
					i++;
					tmp = ft_strjoin(&home[5], &command[i]);
					new_cmd = ft_strjoin(new_cmd, tmp);
				}
			}
			else
				i++;
		}
		printf("end join path : %s\n", new_cmd);
		if (chdir(new_cmd))
		{
			printf("cd: %s: No such file or directory\n", command);
			free(new_cmd);
			return ;
			// g_ret_value = 1;
		}
		free(new_cmd);
		// g_ret_value = 0; */
	}
}

void	ft_cd_home(char *command, t_data *data)
{
	char	*home;

	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return ;
		else if (chdir(&home[5]))
		{
			printf("cd: %s: No such file or directory\n", ft_strjoin(&home[5], command));
			// g_ret_value = 1;
		}
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
	refresh_env(data->env, 1);
	if (!ft_strncmp(command, "~", 2))
	{
		ft_cd_home(command, data);
		return ;
	}
	else if (ft_at_least_charset(command, "~"))
	{
		ft_cd_tild(command, data);
		return ;
	}
	if (chdir(command) != 0)
	{
		printf("cd: %s: No such file or directory\n", command);
		// g_ret_value = 1;
	}
}
