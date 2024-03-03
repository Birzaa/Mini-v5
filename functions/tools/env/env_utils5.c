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
