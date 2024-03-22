/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/22 02:34:38 by abougrai         ###   ########.fr       */
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
	int					status;
	pid_t				pid;
}						t_signal;

extern t_signal			g_sig;

//-----------------------------------------------------> Signal
void					ctrl_c(int sig);
void					ctrl_slash(int sig);
void					ctrl_d(int sig, t_data *data);
void					init_signals(void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~> Builtins

void					ft_export(t_env **env, char **command);
void					ft_unset(t_env *env, char **command);
void					ft_env(t_data *data, char **command);
void					ft_cd(t_data *data, char **command);
void					ft_exit(t_data *data);
void					ft_pwd(t_data *data);
void					ft_echo(char **command);

// ----------------------------------------------------> Functions...

// function/env.c
t_env					*get_env(char **env);

// function/random
void					print_test(void);

// tools/cd/cd_utils1.c
int						ft_is_home_set(t_env *env);
char					*ft_getenv(t_env *env, char *name);

// tools/env/env_utils1.c
t_env					*create_env_part1(t_env *env);
t_env					*ft_env_last(t_env *env);
t_env					*ft_env_new(void *content);
void					print_env(t_env *env);
void					free_env(t_env *env);
void					add_back_env(t_env **env, t_env *new);

// tools/env/env_utils2.c
t_env					*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
void					create_env_part2(t_env **env, int *error);
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
void					replace_content_env(char *oldpwd, char *pwd);
int						check_value_env(char *var);

// tools/expansion/expansion/expansion_utils1.c
int						first_letter(char *content);
int						ft_check_symbol(char *content);
int						ft_strlen_symbol(char *str);
char					*ft_get_symbol_join(char *content);
char					*ft_get_symbol_expand(char *content);

// tools/expansion/expansion/expansion_utils2.c
void					expand_check_letter(t_cmd_word *tmp_word, int *check);
void					expand_check_quote(t_cmd_word *tmp_word);
void					expand_check_expand(t_data *data, t_cmd_word *tmp_word,
							int *check);

// tools/expansion/expansion/expansion_utils3.c
void					expand_check_word(t_cmd_word *tmp_word);
void					expand_check_next(t_cmd_word *tmp_word);
void					expand_continue(t_cmd_word *tmp_word, int *check);
void					expand(t_cmd_word *cmd, t_data *data);
void					parsing_status(t_stack *list);

// tools/export/export_utils1.c
void					replace_export(t_env **env, char *content);
void					print_export(char *content);
int						export_exist(t_env *env, char *content);
int						exp_exist_bis(t_env *env, char *content);
int						ft_export_checking(char *content);

// tools/str
char					*ft_strncpy(char *dest, char *src, unsigned int n);
char					*ft_strcpy(char *s1, char *s2);
int						ft_strcmp(char *s1, char *s2);

// tools/other
void					ft_nothing(void);
int						ft_at_least_charset(char *str, char *charset);
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
char					*get_valid_path(char **command);

// ------------------------>TRAAAASH
void					create_all_file(char **fileNames, int fileCount,
							t_cmd *shell, int d_redir);
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
void					execute_builtin(char **command, t_data *data);
int						is_builtin(char *cmd);

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
int						init_parse(t_data *data);
t_command				*init_command(t_command *list);
t_parsed_cmd			*init_redir(t_parsed_cmd *list);
void					parse_space_in_quote(t_stack *list);

void					index_quote(t_stack *list);

//***********************EXECUTION*********************************
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
	pid_t				pid;
	char				**h_doc_name;
	int					nb_h_doc;
}						t_pipex;

void					execution(t_command *head, char **env, t_data *data);
void					open_redir_in(t_command *head, t_pipex *pipex);
void					open_redir_out(t_command *head, t_pipex *pipex);
void					execute_cmd(char **env, char **valid_cmd);
char					*here_doc(char *av, t_pipex *pipex, int index);
void					create_h_doc(t_command *parsed_cmd, t_pipex *pipex);
void					nb_h_doc(t_command *parsed_cmd, t_pipex *pipex);

//****************************************************************
void					parsing_expand(t_cmd *cmd, t_data *data);

void					handle_no_expand(t_cmd_word *actual, t_cmd_word *next);

#endif