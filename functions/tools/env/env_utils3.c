#include "minishell.h"

char	*ft_get_name_env(char *content)
{
	char	*name;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (content[len] != '=')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	while (content[i] != '=')
	{
		name[i] = content[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_get_value_env(char *content)
{
	char	*value;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 0;
	len = 0;
	while (content[i] != '=')
		i++;
	i++;
	while (content[i + len])
		len++;
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	while (content[i])
		value[j++] = content[i++];
	value[j] = '\0';
	return (value);
}

void	refresh_oldpwd(t_env *env)
{
	t_env	*oldpwd;
	t_env	*tmp;

	oldpwd = env;
	tmp = env;
	while (ft_strncmp(tmp->name, "PWD", 3))
		tmp = tmp->next;
	while (oldpwd)
	{
		if (!ft_strncmp(oldpwd->name, "OLDPWD", 6))
		{
			free(oldpwd->value);
			oldpwd->value = ft_strdup(tmp->value);
			if (!oldpwd->value)
				return ;
			break ;
		}
		oldpwd = oldpwd->next;
	}
}

void	refresh_pwd(t_env *env)
{
	t_env	*tmp;
	char	*pwd;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 3))
		{
			pwd = getcwd(NULL, 0);
			if (!pwd)
				return ;
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tail;
	int		check;

	if (!env)
		return ;
	tail = ft_env_last(env);
	tmp = env;
	check = 0;
	if (tmp->created)
		refresh_oldpwd(env);
	refresh_pwd(env);
	while (tmp && !tmp->created)
	{
		if (!ft_strncmp("_", tmp->content, 1) && ft_strncmp(tail->content,
				tmp->content, 1))
		{
			swap_content_env(tail, tmp);
			check = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(tail->content, "_=/usr/bin/env") && check)
		tail->content = "_=/usr/bin/env";
}
