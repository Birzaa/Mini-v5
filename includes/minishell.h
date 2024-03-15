/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/15 12:56:47 by abougrai         ###   ########.fr       */
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
	NTM = 'Z',
};

typedef struct s_node
{
	char				*content;
	int					len;
	enum e_token		type;
	enum e_state		state;
	int					index;
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

// ------------------------> Redirection

typedef struct s_redir_in
{
	char				**tab;
	int					size;
}						t_redir_in;

typedef struct s_redir_elem
{
	char				*arg;
	int					len;
	enum e_token		type;
	struct s_redir_elem	*next;
}						t_redir_elem;
typedef struct s_redir_list
{
	struct s_redir_elem	*head;
	struct s_redir_elem	*tail;
	int					size;
}						t_redir_list;

// ------------------------> Commande parsing

typedef struct s_cmd_word
{
	char				*content;
	enum e_token		type;
	int					index;
	enum e_state		state;
	struct s_cmd_word	*next;
}						t_cmd_word;

typedef struct s_cmd
{
	t_cmd_word			*words;
	struct s_cmd		*next;
	int					fd;
	int					saved_stdout;
	t_redir_list		*redir;
}						t_cmd;
// *******************PARSING V2

typedef struct s_redir_out
{
	char				*file;
	int					append;
	struct s_redir_out	*next;
	struct s_redir_out	*current;
}						t_redir_out;
typedef struct s_redir_in_2
{
	char				*file;
	int					h_doc;
	struct s_redir_in_2	*next;
	struct s_redir_in_2	*current;
}						t_redir_in_2;
typedef struct s_parsed_cmd
{
	char				**full_cmd;
	t_redir_in_2		*r_in;
	t_redir_out			*r_out;
}						t_parsed_cmd;

typedef struct s_command
{
	t_parsed_cmd		*parsed_cmd;
	struct s_command	*head;
	int					nb_command;
	struct s_command	*next;
	struct s_command	*current;
}						t_command;

// ------------------------> Data

typedef struct s_redir
{
	int					current_file;
	int					i;
	int					len;
}						t_redir;

typedef struct s_data
{
	t_stack				*lex;
	t_cmd				*cmd;
	t_command			*parsed_cmd;
	t_env				*env;
}						t_data;

typedef struct s_signal
{
	int					sigint;
	int					sigquit;
	pid_t				pid;
}						t_signal;

extern t_signal			g_sig;

//-----------------------------------------------------> Signal
void					ctrl_c(int sig);
void					ctrl_slash(int sig);
void					ctrl_d(int sig, t_data *data);
void					init_signals(void);

// ----------------------------------------------------> Redirection...

//	Redirection out
t_redir_list			*parsing_redir(t_cmd *data);

//	Redirection in
void					put_in_tab_file(t_redir_in *r_in, t_cmd *cmd);
void					number_redir_in(t_cmd *cmd, t_redir_in *r_in);
void					open_redir_in(t_redir_in *r_in);

// Tools
t_redir_list			*init_redir_list(t_redir_list *list);
t_redir_elem			*new_redir_node(char *arg, enum e_token type, int len);
void					add_redir_last(t_redir_list *list, t_redir_elem *new);
void					print_redir_list(t_redir_list *redir);

// ----------------------------------------------------> BUILTINS...

// builtins/cd
void					ft_cd_home(char *command, t_data *data);
int						ft_is_home_set(t_env *env);
char					*ft_getenv(t_env *env, char *n);
void					ft_cd(char *command, t_data *data);

// builtins/echo
void					ft_echo(char **content);

// builtins/exit
void					ft_exit(t_data *data);

// builtins/export

void					export_no_arg(t_env *env);
void					export(t_env **env, char *content);

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

// tools/cd/cd_utils1.c
int						ft_is_home_set(t_env *env);
char					*ft_getenv(t_env *env, char *n);

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

// tools/env/env_utils5.c
void					replace_content_env(char *oldpwd, char *pwd);
int						check_value_env(char *var);

// tools/export/export_utils1.c
void					replace_export(t_env **env, char *content);
int						check_export_exist(t_env *env, char *content);
void					print_export(char *content);
int						ft_export_checking(char *content);

// tools/str
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *s1, char *s2);

// tools/other
int						ft_at_least_charset(char *str, char *charset);
void					ft_nothing(void);
int						ft_charcmp(int c, int d);

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

char					**get_tab_env(t_env *env);

// ------------------------> Builtins
void					ft_pwd(t_cmd *shell);
char					*get_valid_path(char **command);
void					ft_cd(char *command, t_data *data);

// ------------------------>TRAAAASH
void					redirection_out(t_cmd *shell, t_redir_list *redir);
void					create_all_file(char **fileNames, int fileCount,
							t_cmd *shell, int d_redir);
char					*ft_stuck(t_redir *redir, char *output_file,
							t_redir_list *redir_two);
void					put_in_tab_filename(char **fileNames, t_redir *redir,
							char *fileName);
void					free_tab_size(char **tab, size_t size);
char					*ft_strncpy(char *dest, char *src, unsigned int n);

// ------------------------>TRAAAASH
void					print_list(t_stack *lst);
void					print_tab(char **tab);
void					ft_free_tab_size(char **tab, int size);
void					print_parsed_cmd(t_command *command);

// test
t_cmd					*new_node_cmd(char *content);
t_cmd					*ft_cmd_last(t_cmd *cmd);
void					add_back_cmd(t_cmd **cmd, t_cmd *new);
void					print_node(t_node *node);
void					print_cmd_list(t_cmd *head);
void	execute_builtin(t_cmd *cmd, char **command, t_data *data);
int	is_builtin(char *cmd);



//********************************************************

t_command				*parse(t_cmd *cmd);
void					parse_r_in(t_cmd_word *cmd, t_redir_in_2 **r_in,
							int h_doc, t_cmd *command);

void					parse_r_out(t_cmd_word *cmd, t_redir_out **r_out,
							int append);

t_command				*ft_command_last(t_command *cmd);
t_command				*ft_command_new(void);
void					add_back_cmd_out(t_command **cmd, t_command *new);
void					parse_word(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd);
void					skip_dr_out(t_cmd *cmd);
void					skip_r_out(t_cmd *cmd);
void					skip_h_doc(t_cmd *cmd);
void					skip_r_in(t_cmd *cmd);
void					skip_word(t_cmd *cmd);
void					free_parser(t_command *head);
void					free_lexer(t_stack *stack);
int						redir_expand(enum e_state *state, char *input,
							t_stack *lst, int i);
void					parse_env(t_cmd_word *cmd, t_data *data);
void					skip_env(t_cmd *cmd);
void					parsing_quote(t_cmd *cmd);
void					init_parse(t_data *data);
t_command				*init_command(t_command *list);
t_parsed_cmd			*init_redir(t_parsed_cmd *list);

void					index_quote(t_stack *list);

//***********************EXECUTION*********************************
void					execution(t_command *head, char **env);
int						open_redir_in2(t_command *head);
int						open_redir_out(t_command *head);
void					execute_cmd(char **env, char **valid_cmd);

//****************************************************************
void					test_exp(t_cmd *cmd, t_data *data);
void					handle_no_expand(t_cmd_word *actual, t_cmd_word *next);

#endif