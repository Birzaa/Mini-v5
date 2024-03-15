#include "minishell.h"

void	replace_export(t_env **env, char *content)
{
	t_env	*tmp;
	int		len_n;
	int		len_c;

	len_c = ft_strlen(content);
	len_n = get_len_to_equal(content);
	tmp = (*env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, content, len_n))
			break ;
		else if (!ft_strncmp(tmp->content, content, len_c))
			break ;
		tmp = tmp->next;
	}
	if (ft_at_least_charset(content, "="))
		tmp->content = content;
}

int	check_export_exist(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;

	if (!content)
		return (1);
	len_c = get_len_to_equal(content);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, content, len_c))
		{
			if (ft_strncmp(tmp->content, content, ft_strlen(content)))
			{
				tmp->content = content;
				return (1);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_export(char *content)
{
	int	i;

	i = 0;
	if (!ft_strncmp("_=", content, 2))
		return ;
	else if (!ft_at_least_charset(content, "="))
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(content, 1);
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_putstr_fd("export ", 1);
	while (content[i] != '=')
		write(1, &content[i++], 1);
	write(1, &content[i++], 1);
	write(1, "\"", 1);
	while (content[i])
		write(1, &content[i++], 1);
	write(1, "\"\n", 2);
}

int	ft_export_checking(char *content)
{
	int	i;

	i = 0;
	if (!isalpha(content[i]) && !ft_charcmp(content[i], '_'))
		return (1);
	return (0);
}
