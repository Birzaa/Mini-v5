#include "minishell.h"

// to do list
// gerer too many args sur cd
// gerer l'expand env $

void	ft_cd_tild(t_data *data, char *command)
{
	char	*new_cmd;
	char	*tmp;
	char	*home;

	home = NULL;
	new_cmd = "";
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		tmp = ft_strjoin(&home[5], command);
		if (!tmp)
			return (perror(""), free(home));
		new_cmd = ft_strjoin(new_cmd, tmp);
		if (!new_cmd)
			return (perror(""), free(home), free(tmp));
		else if (chdir(new_cmd))
		{
			printf("bash: cd: %s: No such file or directory\n", new_cmd);
			return (free(new_cmd), free(home), free(tmp));
			// g_ret_value = 1;
		}
		return (free(new_cmd), free(home), free(tmp));
		// g_ret_value = 0; */
	}
}

void	ft_cd_home(t_data *data, char *command)
{
	char	*home;
	char	*tmp;

	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		if (!check_value_env(home))
			return (free(home));
		else if (chdir(&home[5]))
		{
			tmp = ft_strjoin(&home[5], command);
			if (!tmp)
				return (perror(""), free(home));
			printf("bash: cd: %s: No such file or directory\n", tmp);
			// g_ret_value = 1;
			return (free(tmp), free(home));
		}
		free(home);
		// g_ret_value = 0;
	}
	else
	{
		printf("bash: cd: HOME not set\n");
		// g_ret_value = 1;
	}
}

void	ft_cd(t_data *data, char **command)
{
	refresh_env(data->env, 1);
	if (!command[1] || command[1][0] == '\0')
		return ;
	else if (command[2])
	{
		// g_ret_value = 1;
		return (ft_putstr_fd("bash: cd: too many arguments", 1));
	}
	else if (!ft_strncmp(command[1], "~", 2))
		return (ft_cd_home(data, command[1]));
	else if (!ft_strncmp(command[1], "~/", 2))
		return (ft_cd_tild(data, command[1]));
	if (chdir(command[1]) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", command[1]);
		// g_ret_value = 1;
	}
}
