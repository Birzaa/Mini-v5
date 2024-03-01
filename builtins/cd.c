#include "minishell.h"

/*
	Permet d'obtenir le chemin, sans "".
	ex => cd "functions" = cd functions
 */
char	*get_valid_path(char **command)
{
	char	*valid_path;
	int		len;
	int		i;

	i = 1;
	len = ft_strlen(command[1]);
	valid_path = malloc(len);
	if (valid_path == NULL)
	{
		perror("Malloc error");
		return (NULL);
	}
	if (command[1][0] == '"' && command[1][len - 1] == '"')
	{
		while (i < len - 1)
		{
			valid_path[i - 1] = command[1][i];
			i++;
		}
		valid_path[i - 1] = '\0';
	}
	return (valid_path);
} */

void	ft_cd(char *command, t_data *data)
{
	char	*valid_path;

	(void)data;
	valid_path = command;
	if (valid_path != NULL)
	{
		if (chdir(valid_path) != 0)
			printf("cd: %s: No such file or directory\n", valid_path);
		refresh_env(data->env, 1);
		free(valid_path);
	}
}
