#include "minishell.h"

void	free_multiple_env(t_env *env1, t_env *env2)
{
	free_env(env1);
	free_env(env2);
}

int	get_len_name(char *n)
{
	int	i;

	i = 0;
	while (n[i] != '=')
		i++;
	return (i);
}

char	*ft_strcpy_content_env(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	i++;
	while (s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}
