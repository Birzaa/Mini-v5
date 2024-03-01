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

char	*ft_strcpy_content_env(char *s1, char *s2, char *n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (n[j])
		s1[i++] = n[j++];
	while (s2[k])
		s1[i++] = s2[k++];
	s1[i] = '\0';
	return (s1);
}

void	print_pwd_env(void)
{
	char	*pwd;

	pwd = NULL;
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return ;
		ft_putstr_fd("PWD=", 1);
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
		free(pwd);
	}
}
