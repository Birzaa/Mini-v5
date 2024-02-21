/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:28 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 13:43:06 by thenwood         ###   ########.fr       */
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
	char			*str;
	struct t_env	*next;

}					t_env;

// ------------------------> Data

typedef struct s_data
{
	t_stack			*lex;
	t_env			*env;
}					t_data;

// ----------------------------------------------------> Functions...

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

// ------------------------>TRAAAASH
void				print_list(t_stack *lst);

#endif