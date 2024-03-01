#include "minishell.h"

void	replace_content_env(char *oldpwd, char *pwd)
{
	int	len_oldpwd;
	int	len_pwd;

	len_oldpwd = get_len_name(oldpwd);
	len_pwd = get_len_name(pwd);
	while (pwd[len_pwd])
		oldpwd[len_oldpwd++] = pwd[len_pwd++];
	oldpwd[len_oldpwd] = '\0';
}

char	*ft_strdup_value_env(char *value, int len_n, int len_value)
{
	char	*cpy;
	int		i;

	cpy = ft_calloc(sizeof(char), len_value);
	if (!cpy)
		return (NULL);
	i = 0;
	while (value[len_n])
		cpy[i++] = value[len_n++];
	cpy[i] = '\0';
	return (cpy);
}
// n = nom de la variable env
// value = la value de n
// gne prend data->env et le nombre d'une variable env
// gne renvoie la value d'une variable d'env correspondante au nom
// cette variable est freeable et null terminated
// si aucun nom ne correspond, la fonction renvoie une chaine freeable nullc

char	*get_name_expansion(t_env *env, char *n)
{
	int		len_n;
	int		len_value;
	char	*name;

	len_value = 0;
	len_n = ft_strlen(n);
	while (env)
	{
		if (!ft_strncmp(env->content, n, len_n))
		{
			if (!ft_at_least_charset(env->content, "="))
			{
				env->content = ft_strdup(n);
				if (env->content)
					return (NULL);
				return (env->content);
			}
			else if (env->content[len_n] == '=')
				len_value = ft_strlen(env->content) - len_n;
			name = ft_strdup_value_env(env->content, len_n + 1, len_value);
			return (name);
		}
		env = env->next;
	}
	name = ft_calloc(1, 1);
	return (name);
}

// 2eme version de l'env expand avec directemet name et value
/* char	*get_name_expansion_bis(t_env *env, char *n)
{
	int		len_n;
	char	*name;

	len_n = ft_strlen(n);
	while (env)
	{
		if (!ft_strncmp(env->name, n, len_n) && env->content[len_n] == '=')
			return (env->value);
		env = env->next;
	}
	name = ft_calloc(1, 1);
	return (name);
} */
