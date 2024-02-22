/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/22 12:40:22 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREEN "\033[1;32m"
# define ORANGE "\033[38;5;216m"
# define RESET "\033[0m"
# define BLUE "\033[1;34m"
# define EQUAL 0

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

// ------------------------------------------------------> Structure

// ------------------------> Lexer

enum				e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};
enum				e_token
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
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*head;
	t_node			*tail;
	int				size;
}					t_stack;

// env
typedef struct s_env
{
	char			*content;
	int				size;
	struct s_env	*next;

}					t_env;

// ------------------------> Data

typedef struct s_data
{
	t_stack			*lex;
	t_env			*env;
}					t_data;

typedef struct s_signal
{
}					t_signal;

// ----------------------------------------------------> BUILTINS...
// builtins/export
void				export_no_arg(t_env *env);
void				export(t_env **env, char *content);

// builtins/unset
void				del_node_env(t_env *target, t_env *previous);
void				pop_node_env(t_env *env);
void				unset(t_env *env, char *name);

// ----------------------------------------------------> Functions...

// function/env.c
t_env				*get_env(char **env);

// tools/env/env_utils1.c
t_env				*ft_env_last(t_env *env);
t_env				*ft_env_new(void *content);
void				print_env(t_env *env);
void				free_env(t_env *env);
void				add_back_env(t_env **env, t_env *new);

// tools/env/env_utils2.c
t_env				*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
int					ft_envsize(t_env *env);
void				del_node_env(t_env *target, t_env *previous);
void				swap_content_env(t_env *node1, t_env *node2);
void				pop_node_env(t_env *env);

// tools/str
int					ft_strcmp(char *s1, char *s2);

// ------------------------> Parsing
t_stack				*lexer(char *input);
int					is_charset(char c);

//------> list
t_node				*new_node(char *content, int len, enum e_token type,
						enum e_state state);
void				lst_add_back(t_stack *lst, t_node *node);
t_stack				*malloc_lst(t_stack *stack);

//------> Get right token
int					word_token(enum e_state state, char *input, t_stack *lst);
void				quote_token(enum e_state *state, char *input, t_stack *lst,
						int quote);
int					redir_token(enum e_state *state, char *input, t_stack *lst,
						int i);

//------> Tools
int					ft_isspace(char c);

// ------------------------>TRAAAASH
void				print_list(t_stack *lst);

#endif