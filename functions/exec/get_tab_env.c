#include "minishell.h"

char	**get_tab_env(t_env *env)
{
	char	**tab_env;
	char	*temp;
	t_env	*tmp;
	int		tab_size;
	int		i;

	i = 0;
	tmp = env;
	tab_size = ft_envsize(env);
	tab_env = malloc(tab_size * sizeof(char *) + 1);
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		temp = ft_strdup(tmp->content);
		if (!temp)
		{
			ft_free_tab(tab_env);
			return (NULL);
		}
		tab_env[i++] = temp;
		tmp = tmp->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}