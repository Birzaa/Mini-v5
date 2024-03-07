#include "minishell.h"

int	ft_is_home_set(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
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
