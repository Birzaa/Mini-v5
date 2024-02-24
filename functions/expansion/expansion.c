#include "minishell.h"

char	*ft_strcpy_value_env(char *value, int len_n, int len_value)
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

	len_n = ft_strlen(n);
	while (env)
	{
		if (!ft_strncmp(env->content, n, len_n) && env->content[len_n] == '=')
		{
			len_value = ft_strlen(env->content) - len_n;
			name = ft_strcpy_value_env(env->content, len_n + 1, len_value);
			return (name);
		}
		env = env->next;
	}
	name = ft_calloc(1, 1);
	return (name);
}
