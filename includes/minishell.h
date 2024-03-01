/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/01 17:27:13 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREEN "\033[1;32m"
# define ORANGE "\033[38;5;216m"
# define RESET "\033[0m"
# define BLUE "\033[1;34m"
# define EQUAL 0

# define OLDPWD_ENV "OLDPWD="
# define COLORS_ENV "LS_COLORS="
# define SHLVL_ENV "SHLVL=1"
# define PTH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define _ENV "_=/usr/bin/env"

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

// ------------------------------------------------------> Structure

// ------------------------> Lexer

enum					e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};
enum					e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

typedef struct s_node
{
	char				*content;
	int					len;
	enum e_token		type;
	enum e_state		state;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*head;
	t_node				*tail;
	int					size;
}						t_stack;

// env
typedef struct s_env
{
	char				*content;
	int					size;
	struct s_env		*next;

}						t_env;

// ------------------------> Commande parsing

typedef struct s_cmd_word
{
	char				*content;
	enum e_token		type;
	enum e_state		state;
	struct s_cmd_word	*next;
}						t_cmd_word;

typedef struct s_cmd
{
	t_cmd_word			*words;
	struct s_cmd		*next;
	int					fd;
	int					saved_stdout;
}						t_cmd;

// ------------------------> Data

typedef struct s_redir
{
	size_t				current_file;
	int					i;
	int					len;
}						t_redir;

typedef struct s_data
{
	t_stack				*lex;
	t_cmd				*cmd;
	t_env				*env;
}						t_data;

typedef struct s_signal
{
	int					sigint;
	int					sigquit;
	pid_t				pid;
}						t_signal;

// ----------------------------------------------------> BUILTINS...

//cd
void	ft_cd(char **command);

// builtins/exit
void					ft_exit(t_data *data);

// builtins/export
int						check_export_exit(t_env *env, char *content);
void					print_export(char *content);
void					export_no_arg(t_env *env);
void					export(t_env **env, char *content);
void					replace_export(t_env **env, char *content);

// builtins/unset
void					del_node_env(t_env *target, t_env *previous);
void					pop_node_env(t_env *env);
void					unset(t_env *env, char *name);

// ----------------------------------------------------> Functions...

// function/env.c
t_env					*get_env(char **env);

// function/expansion
void					replace_content_env(char *oldpwd, char *pwd);

char					*ft_strdup_value_env(char *value, int len_n,
							int len_value);
char					*get_name_expansion(t_env *env, char *n);

// function/random
void					print_test(void);

// tools/env/env_utils1.c
t_env					*create_env_part1(t_env *env);
t_env					*ft_env_last(t_env *env);
t_env					*ft_env_new(void *content);
void					print_env(t_env *env);
void					free_env(t_env *env);
void					add_back_env(t_env **env, t_env *new);

// tools/env/env_utils2.c
void					create_env_part2(t_env **env, int *error);
t_env					*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
int						ft_envsize(t_env *env);
void					del_node_env(t_env *target, t_env *previous);
void					swap_content_env(t_env *node1, t_env *node2);
void					pop_node_env(t_env *env);

// tools/env/env_utils3.c
char					*ft_get_name_env(char *content);
char					*ft_get_value_env(char *content);
void					refresh_oldpwd(t_env *env);
void					refresh_pwd(t_env *env);
void					refresh_env(t_env *env, int cd);

// tools/env/env_utils4.c
char					*ft_strcpy_content_env(char *s1, char *s2, char *n);
void					free_multiple_env(t_env *env1, t_env *env2);
int						get_len_name(char *n);
void					print_pwd_env(void);
int						get_len_to_equal(char *content);

// tools/str
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *s1, char *s2);

// tools/other
int						ft_contain_charset(char c, char *charset);
int						ft_at_least_charset(char *str, char *charset);

// ------------------------> Parsing
t_stack					*lexer(char *input);
int						is_charset(char c);
t_cmd					*parser(t_stack *lst);

//------> Syntax error
int						is_invalid_pipe(t_node *node);
int						ft_perror(char *str, char *option);
int						error_cmd(t_stack *lst);
int						is_redir(enum e_token type);
int						is_invalid_redir(t_node *node);

//------> list
t_node					*new_node(char *content, int len, enum e_token type,
							enum e_state state);
void					lst_add_back(t_stack *lst, t_node *node);
t_stack					*malloc_lst(t_stack *stack);

//------> Get right token
int						word_token(enum e_state state, char *input,
							t_stack *lst);
void					quote_token(enum e_state *state, char *input,
							t_stack *lst, int quote);
int						redir_token(enum e_state *state, char *input,
							t_stack *lst, int i);

//------> Tools
int						ft_isspace(char c);
void					free_list(t_stack *list);

// ------------------------> Execution
char					**get_cmd(t_cmd *cmd);
void					exec(t_cmd *cmd, char **env, t_data *data);
char					**find_path(char **env);
char					*valid_path(char **all_paths, char *cmd);
void					ft_free_tab(char **tab);

// ------------------------> Builtins
void					ft_pwd(t_cmd *shell);
char					*get_valid_path(char **command);
void					ft_cd(char *command, t_data *data);

// ------------------------>TRAAAASH
void					redirection_out(t_cmd *shell);
void					create_all_file(char **fileNames, size_t fileCount,
							t_cmd *shell);
char					*ft_stuck(char *command, t_redir *redir,
							char *output_file);
void					put_in_tab_filename(char **fileNames, t_redir *redir,
							char *fileName);
void					free_tab_size(char **tab, size_t size);
char					*ft_strncpy(char *dest, char *src, unsigned int n);

// ------------------------>TRAAAASH
void					print_list(t_stack *lst);

// test
t_cmd					*new_node_cmd(char *content);
t_cmd					*ft_cmd_last(t_cmd *cmd);
void					add_back_cmd(t_cmd **cmd, t_cmd *new);
void					print_node(t_node *node);

#endif