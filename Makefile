# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[1;36m
MAGENTA = \033[0;35m
ORANGE = \033[38;5;216m
NC = \033[0m

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Project
NAME = minishell
HEADER_DIR = ./includes/
OBJ_DIR = objects/
SRC_DIR = functions/
PARSING_DIR = functions/parsing/
PARSER_DIR = functions/parsing/parser/
LEXER_DIR = functions/parsing/lexer/
EXECUTION_DIR = functions/exec/
BUILTINS_DIR = builtins/
TRASH_DIR = functions/TRAAASH/
TOOL_DIR = functions/tools/
SRC = $(SRC_DIR)main.c \
	$(LEXER_DIR)lexer.c \
	$(LEXER_DIR)token.c \
	$(LEXER_DIR)tools.c \
	$(LEXER_DIR)lst_tools.c \
	$(PARSER_DIR)parser.c \
	$(PARSER_DIR)final_cmd.c \
	$(PARSER_DIR)redir_in.c \
	$(PARSER_DIR)quote.c \
	$(PARSER_DIR)space_in_quote.c \
	$(PARSER_DIR)redir_out.c \
	$(PARSER_DIR)expansion.c \
	$(PARSER_DIR)skip.c \
	$(PARSER_DIR)index_quote.c \
	$(PARSER_DIR)cmd_next.c \
	$(PARSER_DIR)word.c \
	$(PARSER_DIR)word_bis.c \
	$(PARSER_DIR)env.c \
	$(PARSER_DIR)status.c \
	$(PARSER_DIR)handle_no_expand.c \
	$(PARSING_DIR)error_syntax.c \
	$(PARSING_DIR)syntax.c \
	$(SRC_DIR)env/get_env.c \
	$(SRC_DIR)tools/str/ft_strncpy.c \
	$(SRC_DIR)tools/str/ft_strcmp.c \
	$(SRC_DIR)tools/str/ft_strcpy.c \
	$(SRC_DIR)tools/cd/cd_utils1.c \
	$(SRC_DIR)tools/env/env_utils1.c \
	$(SRC_DIR)tools/env/env_utils2.c \
	$(SRC_DIR)tools/env/env_utils3.c \
	$(SRC_DIR)tools/env/env_utils4.c \
	$(SRC_DIR)tools/env/env_utils5.c \
	$(SRC_DIR)tools/expansion/expansion_utils1.c \
	$(SRC_DIR)tools/expansion/expansion_utils2.c \
	$(SRC_DIR)tools/expansion/expansion_utils3.c \
	$(SRC_DIR)tools/export/export_utils1.c \
	$(SRC_DIR)tools/export/export_utils2.c \
	$(SRC_DIR)tools/export/export_utils3.c \
	$(SRC_DIR)tools/export/export_utils4.c \
	$(SRC_DIR)tools/other/ft_at_least_equal.c\
	$(SRC_DIR)tools/other/ft_nothing.c\
	$(SRC_DIR)tools/other/ft_charcmp.c\
	$(SRC_DIR)tools/other/ft_tab_len.c\
	$(SRC_DIR)tools/quote/quote_utils1.c\
	$(SRC_DIR)signal/signal.c\
	$(BUILTINS_DIR)env.c \
	$(BUILTINS_DIR)echo.c \
	$(BUILTINS_DIR)pwd.c \
	$(BUILTINS_DIR)exit.c \
	$(BUILTINS_DIR)cd.c \
	$(BUILTINS_DIR)export.c \
	$(BUILTINS_DIR)unset.c \
	$(TRASH_DIR)print.c \
	$(TRASH_DIR)print_test.c \
	$(EXECUTION_DIR)get_tab_env.c \
	$(EXECUTION_DIR)path.c \
	$(EXECUTION_DIR)exec.c \
	$(EXECUTION_DIR)redir.c \
	$(EXECUTION_DIR)bin.c \
	$(EXECUTION_DIR)child.c \
	$(EXECUTION_DIR)builtin.c \
	$(EXECUTION_DIR)clean_exec.c \
	$(EXECUTION_DIR)h_doc.c \
	$(EXECUTION_DIR)h_doc_bis.c \
	$(TOOL_DIR)lst/free.c \
	$(TOOL_DIR)free/free_parser.c \
	$(TOOL_DIR)free/free_parser_two.c \
	$(TOOL_DIR)free/free_lexer.c \
	$(TOOL_DIR)free/free_exec.c \
	$(TOOL_DIR)error/error.c \

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

#Libft
LIBFT_A = ./libft/libft.a

all: $(NAME)

$(LIBFT_A):
	@make -s -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
	@echo "$(CYAN)Compiled $<$(NC)"

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJS) $(LIBFT_A) -lreadline -o $@ && \
		echo "${MAGENTA}$@ ${GREEN}Compiled successfully${NC}" || \
		echo "${RED}Failed to compile ${CYAN}$@${NC}"

run : ${NAME}
	@./${NAME}

valgrind : ${NAME}
	@ valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./${NAME}

runv : ${NAME}
	@ valgrind --leak-check=full --suppressions=supp.supp --trace-children=yes --track-fds=yes ./${NAME}

env : ${NAME}
	@env -i ./${NAME}

envv : ${NAME}
	@env -i valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./${NAME}

clean:
	@rm -rf $(OBJ_DIR)
	@make -s clean -C ./libft
	@echo "${YELLOW}Finished cleaning${NC}"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_A)
	@echo "${YELLOW}Complete cleaning completed${NC}"

re: fclean all

.PHONY: all clean fclean re
