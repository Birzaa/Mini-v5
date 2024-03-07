#include "minishell.h"

// to do list
// gerer too many args sur cd
// gerer l'expand env $

void	ft_cd_tild(char *command, t_data *data)
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
			return ;
		tmp = ft_strjoin(&home[5], command);
		if (!tmp)
			return (free(home));
		new_cmd = ft_strjoin(new_cmd, tmp);
		if (!new_cmd)
			return (free(home), free(tmp));
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

void	ft_cd_home(char *command, t_data *data)
{
	char	*home;
	char	*tmp;

	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return ;
		if (!check_value_env(home))
			return (free(home));
		else if (chdir(&home[5]))
		{
			tmp = ft_strjoin(&home[5], command);
			if (!tmp)
				return (free(home));
			printf("bash: cd: %s: No such file or directory\n", tmp);
			// g_ret_value = 1;
			return (free(tmp), free(home));
		}
		free(home);
		// g_ret_value = 0;
	}
	else
		printf("bash: cd: HOME not set\n");
	// g_ret_value = 1;
}

void	ft_cd(char *command, t_data *data)
{
	refresh_env(data->env, 1);
	if (!command)
		return ;
	if (!ft_strncmp(command, "~", 2))
	{
		ft_cd_home(command, data);
		return ;
	}
	else if (!ft_strncmp(command, "~/", 2))
	{
		ft_cd_tild(&command[1], data);
		return ;
	}
	if (chdir(command) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", command);
		// g_ret_value = 1;
	}
}
