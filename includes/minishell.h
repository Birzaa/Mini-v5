/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 09:29:50 by abougrai         ###   ########.fr       */
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
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
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
	int					no_free;
	int					status_free;
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
	int					exported;
	int					size;
	struct s_env		*next;
	char				**envp;

}						t_env;

// ------------------------> Commande parsing

typedef struct s_cmd_word
{
	char				*content;
	enum e_token		type;
	int					index;
	int					expand;
	int					need_split;
	enum e_state		state;
	struct s_cmd_word	*next;
}						t_cmd_word;

typedef struct s_cmd
{
	t_cmd_word			*words;
	struct s_cmd		*next;
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
	int					nb_cmd;
}						t_parsed_cmd;

typedef struct s_command
{
	t_parsed_cmd		*parsed_cmd;
	struct s_command	*head;
	int					nb_command;
	struct s_command	*next;
	struct s_command	*current;
}						t_command;

// ------------------------> Execution

typedef struct s_pipex
{
	int					infile;
	int					outfile;
	int					*pipe;
	int					idx;
	int					nb_cmd;
	int					saved_in;
	int					saved_out;
	int					h_doc;
	int					fd_echo;
	pid_t				pid;
	char				**h_doc_name;
	int					nb_h_doc;
	int					need_free;
	int					need_exec;
	int					jss_a_terre;
}						t_pipex;

// ------------------------> Data

typedef struct s_data
{
	t_stack				*lex;
	t_cmd				*cmd;
	t_command			*parsed_cmd;
	t_env				*env;
	char				**envp;
	int					nb_input;
	int					tab_created;
}						t_data;

typedef struct s_signal
{
	int					sigint;
	int					sigquit;
	int					status;
	char				*input;
	int					here_doc;
	pid_t				pid;
}						t_signal;

extern t_signal			g_sig;

//-----------------------------------------------------> Signal
void					ctrl_c(int sig);
void					ctrl_slash(int sig);
void					ctrl_d(int sig);
void					init_signals(void);
void					exec_here_doc(int sig);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~> Builtins

void					ft_export(t_env **env, char **command);
void					ft_unset(t_env *env, char **command);
void					ft_env(t_data *data, char **command);
void					ft_cd(t_data *data, char **command);
void					ft_exit(t_data *data, t_pipex *p, char **command);
void					ft_exit_two(t_data *data);
void					ft_pwd(t_data *data);
void					ft_echo(char **command, t_pipex *p);

// ----------------------------------------------------> Functions...

// function/env.c
t_env					*get_env(char **env);
char					**create_env(void);

// function/random
void					print_test(void);

// tools/cd/cd_utils1.c
int						ft_is_home_set(t_env *env);
char					*ft_getenv(t_env *env, char *name);
void					ft_error_cd(char *tmp, char *command, char *home);

// tools/env/env_utils1.c
t_env					*create_env_part1(t_env *env);
t_env					*ft_env_last(t_env *env);
t_env					*ft_env_new(void *content);
void					print_env(t_env *env);
void					free_env(t_env *env);
void					add_back_env(t_env **env, t_env *new);

// tools/env/env_utils2.c
t_env					*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
void					create_env_part2(t_env **env);
void					del_node_env(t_env *target, t_env *previous);
void					swap_content_env(t_env *node1, t_env *node2);
void					pop_node_env(t_env *env);
int						ft_envsize(t_env *env);

// tools/env/env_utils3.c
void					refresh_env(t_env *env, int cd);
void					refresh_oldpwd(t_env *env);
void					refresh_pwd(t_env *env);
char					*ft_get_name_env(char *content);
char					*ft_get_value_env(char *content);

// tools/env/env_utils4.c
void					free_multiple_env(t_env *env1, t_env *env2);
void					print_pwd_env(void);
int						get_len_name(char *n);
int						get_len_to_equal(char *content);
char					*ft_strcpy_content_env(char *s1, char *s2, char *n);

// tools/env/env_utils5.c
t_env					*ft_env_new_export(void *content);
void					replace_content_env(char *oldpwd, char *pwd);
int						check_value_env(char *var);
int						ft_getenv_check(t_env *env, char *n);
int						ft_getenv_check_tab(char **tab, char *path);

// tools/expansion/expansion/expansion_utils1.c
int						first_letter(char *content);
int						ft_check_symbol(char *content);
int						ft_strlen_symbol(char *str);
char					*ft_get_symbol_join(char *content);
char					*ft_get_symbol_expand(char *content);

// tools/expansion/expansion/expansion_utils2.c
void					expand_check_no_sym(t_data *data, t_cmd_word *env,
							t_cmd_word *word, int expanded);
void					expand(t_cmd_word *cmd, t_data *data);
void					expand_whitespace(t_cmd_word *tmp_word);
void					while_expand(t_data *data, t_cmd_word *tmp_word);

// tools/expansion/expansion/expansion_utils3.c
int						tmp_expand_null(t_cmd_word *cmd, char *tmp_expand,
							char *tmp_join);
int						full_and_join_null(t_cmd_word *cmd, char *tmp_expand,
							char *tmp_join, char *tmp_full);
int						ft_expand_no_symbol_short(t_cmd_word *word);
void					ft_expand_symbol_short(t_cmd_word *cmd, char *tmp_full);
int						ft_expand_no_symbol_short(t_cmd_word *word);

// tools/export/export_utils1.c
void					replace_export(t_env **env, char *content);
void					print_export(char *content);
int						export_exist(t_env *env, char *content);
int						exp_exist_bis(t_env *env, char *content);
int						ft_export_checking(char *content);

// tools/export/export_utils2.c
void					handle_replace_export(t_env *tmp, char *content);
char					*ft_get_real_export_name(char *content, char *cpy);
int						ft_export_add_checking(char *cmd);
int						ft_export_op(t_env *env, char *content);
int						ft_export_exist_for_add(t_env *env, char *content);

// tools/export/export_utils3.c
t_env					*ft_get_target_export(t_env *env, char *content);
t_env					*ft_env_new_export_add(void *join);
void					export_new_add_back_add(t_env **env, char *join);
char					*ft_export_join_content(t_env *env, char *content);

// tools/export/export_utils4.c
int						ft_export_add_case_one(t_env *env, char *join,
							char *name, char *value);
int						ft_export_add_case_two(t_env *env, char *name,
							char *value);

// tools/str
char					*ft_strncpy(char *dest, char *src, unsigned int n);
char					*ft_strcpy(char *s1, char *s2);
int						ft_strcmp(char *s1, char *s2);

// tools/other
void					ft_nothing(void);
int						ft_at_least_charset(char *str, char *charset);
int						ft_charcmp(int c, int d);
int						ft_tab_len(char **tab);

// tools/quote/quote_utils1.c
void					quote_case_one(t_cmd_word *tmp_word);
void					quote_case_two(t_cmd_word *tmp_word);

// ------------------------> Parsing
t_stack					*lexer(char *input);
int						is_charset(char c);
t_cmd					*parser(t_stack *lst);

// parser/expansion.c
void					parsing_expand(t_cmd *cmd, t_data *data);
char					*ft_expand_symbol_bis(t_env *env, t_cmd_word *cmd,
							char *tmp_expand);
int						ft_expand_symbol(t_env *env, t_cmd_word *cmd);
int						ft_expand_exist(t_env *env, t_cmd_word *cmd);
int						ft_expand_no_symbol(t_env *env, t_cmd_word *word);

// parser/status.c
void					parsing_status(t_stack *list);

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
void					free_parsed_cmd(t_parsed_cmd *parsed_cmd);
void					free_list(t_stack *list);
void					free_command(t_command *command);

// ------------------------> Execution
char					**get_cmd(t_cmd *cmd);
void					exec(t_cmd *cmd, char **env, t_data *data);
char					**find_path(char **env);
char					*valid_path(char **all_paths, char *cmd);
void					ft_free_tab(char **tab);
char					**get_tab_env(t_env *env);
void					free_exec(t_pipex *pipex);

// ------------------------> Builtins
char					*get_valid_path(char **command);

// ------------------------>TRAAAASH
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
void					execute_builtin(char **command, t_data *data,
							t_pipex *p);
int						is_builtin(char *cmd);

//********************************************************

t_command				*parse(t_cmd *cmd, t_data *data);
void					parse_r_in(t_cmd_word *cmd, t_redir_in_2 **r_in,
							int h_doc, t_cmd *command);

void					parse_r_out(t_cmd_word *cmd, t_redir_out **r_out,
							int append);

t_command				*ft_command_last(t_command *cmd);
t_command				*ft_command_new(void);
void					add_back_cmd_out(t_command **cmd, t_command *new);
void					parse_word(t_cmd_word *cmd, t_parsed_cmd *parsed_cmd);
void					skip_dr_out(t_cmd_word **cmd);
void					skip_r_out(t_cmd_word **cmd);
void					skip_h_doc(t_cmd_word **cmd);
void					skip_r_in(t_cmd_word **cmd);
void					skip_word(t_cmd_word **cmd);
void					free_parser(t_cmd *head, t_command *command);
void					free_lexer(t_stack *stack);
int						redir_expand(enum e_state *state, char *input,
							t_stack *lst, int i);
void					parse_env(t_cmd_word *cmd, t_data *data);
void					skip_env(t_cmd_word *cmd);
void					parsing_quote(t_cmd *cmd);
int						init_parse(t_data *data);
t_command				*init_command(t_command *list);
t_parsed_cmd			*init_redir(t_parsed_cmd *list);
void					parse_space_in_quote(t_stack *list);

void					index_quote(t_stack *list);

//***********************EXECUTION*********************************

void					execution(t_command *head, char **env, t_data *data);
void					open_redir_in(t_command *head, t_pipex *pipex);
void					open_redir_out(t_command *head, t_pipex *pipex);
void					close_h_doc(t_pipex *pipex);
void					execute_cmd(char **env, char **valid_cmd, t_data *data,
							t_pipex *p);
char					*here_doc(char *av, t_pipex *pipex, int index,
							char **tab, t_data *data);
void					create_h_doc(t_command *parsed_cmd, t_pipex *pipex,
							char **tab, t_data *data);
void					nb_h_doc(t_command *parsed_cmd, t_pipex *pipex);
void					parent_free(t_pipex *pipex);
void					handle_signal(int sig);

void					caca(t_command *parsed_cmd, t_pipex *pipex, char **tab,
							t_data *data);

//****************************************************************
void					parsing_expand(t_cmd *cmd, t_data *data);

void					handle_no_expand(t_cmd_word *actual, t_cmd_word *next);
void					handle_error(char *s1, char *s2);
void					handle_error_cd(char *s1, char *s2);
void					handle_error_export(char *s1);
int						c_words(char const *str, char set);

#endif