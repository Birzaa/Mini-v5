#include "minishell.h"

char	**get_tab_env(t_env *env)
{
	char	**tab_env;
	char	*temp;
	t_env	*tmp;
	int		tab_size;
	int		i;

	i = 0;
	tab_size = ft_envsize(env);
	printf("taille tableau %d", tab_size);
	tmp = env;
	tab_env = malloc(70 * sizeof(char *) + 1);
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		print_test();
		temp = ft_strdup(tmp->content);
		if (temp)
		{
			ft_free_tab(tab_env);
			return (NULL);
		}
		tab_env[i++] = temp;
		free(temp);
		tmp = tmp->next;
	}
	tab_env[i] = "\0";
	return (tab_env);
}
