/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:44:49 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/03 13:25:25 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_error_cd(char *tmp, char *command, char *home)
{
	tmp = ft_strjoin(&home[5], command);
	if (!tmp)
		return (perror(""), free(home));
	printf("bash: cd: %s: No such file or directory\n", tmp);
	g_sig.status = 1;
	return (free(tmp), free(home));
}

/* void	cd_no_arg(void)
{
	
} */