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
BUILTINS_DIR = builtins/
TRASH_DIR = functions/TRAAASH/
SRC = $(SRC_DIR)main.c \
	$(PARSING_DIR)lexer.c \
	$(PARSING_DIR)token.c \
	$(PARSING_DIR)tools.c \
	$(PARSING_DIR)lst_tools.c \
	$(PARSING_DIR)parser.c \
	$(SRC_DIR)env/get_env.c \
	$(SRC_DIR)expansion/expansion.c \
	$(SRC_DIR)tools/str/ft_strcmp.c \
	$(SRC_DIR)tools/env/env_utils1.c \
	$(SRC_DIR)tools/env/env_utils2.c \
	$(BUILTINS_DIR)export.c \
	$(BUILTINS_DIR)unset.c \
	$(BUILTINS_DIR)env.c \
	$(TRASH_DIR)print.c \
	$(TRASH_DIR)print_test.c \

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
	@ valgrind ./${NAME}

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
