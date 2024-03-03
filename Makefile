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
REDIRECTION_DIR = functions/redirection/
EXECUTION_DIR = functions/exec/
BUILTINS_DIR = builtins/
TRASH_DIR = functions/TRAAASH/
TOOL_DIR = functions/tools/
SRC = $(SRC_DIR)main.c \
	$(PARSING_DIR)lexer.c \
	$(PARSING_DIR)token.c \
	$(PARSING_DIR)tools.c \
	$(PARSING_DIR)lst_tools.c \
	$(PARSING_DIR)parser.c \
	$(PARSING_DIR)error_syntax.c \
	$(PARSING_DIR)syntax.c \
	$(PARSING_DIR)redir.c \
	$(PARSING_DIR)redir_tools.c \
	$(SRC_DIR)env/get_env.c \
	$(SRC_DIR)expansion/expansion.c \
	$(SRC_DIR)tools/str/ft_strcmp.c \
	$(SRC_DIR)tools/str/ft_strcpy.c \
	$(SRC_DIR)tools/env/env_utils1.c \
	$(SRC_DIR)tools/env/env_utils2.c \
	$(SRC_DIR)tools/env/env_utils3.c \
	$(SRC_DIR)tools/env/env_utils4.c \
	$(SRC_DIR)tools/env/env_utils5.c \
	$(SRC_DIR)tools/other/ft_at_least_equal.c\
	$(BUILTINS_DIR)env.c \
	$(BUILTINS_DIR)pwd.c \
	$(BUILTINS_DIR)exit.c \
	$(BUILTINS_DIR)cd.c \
	$(BUILTINS_DIR)export.c \
	$(BUILTINS_DIR)unset.c \
	$(TRASH_DIR)print.c \
	$(TRASH_DIR)print_test.c \
	$(REDIRECTION_DIR)redirection.c \
	$(REDIRECTION_DIR)redirection_scnd.c \
	$(EXECUTION_DIR)get_tab_env.c \
	$(EXECUTION_DIR)exec.c \
	$(EXECUTION_DIR)path.c \
	$(TOOL_DIR)lst/free.c \

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
	@ valgrind --leak-check=full --suppressions=supp.supp ./${NAME}

runv : ${NAME}
	@ valgrind --leak-check=full --suppressions=supp.supp ./${NAME}

env : ${NAME}
	@env -i ./${NAME}

envv : ${NAME}
	@env -i valgrind --leak-check=full --suppressions=supp.supp ./${NAME}

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
