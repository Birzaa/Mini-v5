# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN=\033[1;36m
MAGENTA = \033[0;35m
NC = \033[0m

#LIBFT
NAME = libft.a
HEADER_DIR = ./includes/
OBJ_DIR = objects/
SRC_DIR = functions/

SRC = \
    $(SRC_DIR)nbr/ft_atoi.c \
    $(SRC_DIR)nbr/ft_itoa.c \
    $(SRC_DIR)nbr/ft_putnbr_fd.c \
    \
    $(SRC_DIR)str/ft_putstr_fd.c \
    $(SRC_DIR)str/ft_split.c \
    $(SRC_DIR)str/ft_strchr.c \
    $(SRC_DIR)str/ft_strdup.c \
    $(SRC_DIR)str/ft_striteri.c \
    $(SRC_DIR)str/ft_strjoin.c \
    $(SRC_DIR)str/ft_strlcat.c \
    $(SRC_DIR)str/ft_strlcpy.c \
    $(SRC_DIR)str/ft_strlen.c \
    $(SRC_DIR)str/ft_strmapi.c \
    $(SRC_DIR)str/ft_strncmp.c \
    $(SRC_DIR)str/ft_strnstr.c \
    $(SRC_DIR)str/ft_strrchr.c \
    $(SRC_DIR)str/ft_strtrim.c \
    $(SRC_DIR)str/ft_substr.c \
    $(SRC_DIR)str/ft_tolower.c \
    $(SRC_DIR)str/ft_toupper.c \
    $(SRC_DIR)str/ft_bzero.c \
    $(SRC_DIR)str/ft_putchar_fd.c \
    $(SRC_DIR)str/ft_putendl_fd.c \
    \
    $(SRC_DIR)other/ft_calloc.c \
    \
    $(SRC_DIR)is/ft_isalnum.c \
    $(SRC_DIR)is/ft_isalpha.c \
    $(SRC_DIR)is/ft_isascii.c \
    $(SRC_DIR)is/ft_isdigit.c \
    $(SRC_DIR)is/ft_isprint.c \
    \
    $(SRC_DIR)mem/ft_memchr.c \
    $(SRC_DIR)mem/ft_memcmp.c \
    $(SRC_DIR)mem/ft_memcpy.c \
    $(SRC_DIR)mem/ft_memmove.c \
    $(SRC_DIR)mem/ft_memset.c \
    \
    $(SRC_DIR)lst/ft_lstnew.c \
    $(SRC_DIR)lst/ft_lstadd_front.c \
    $(SRC_DIR)lst/ft_lstsize.c \
    $(SRC_DIR)lst/ft_lstlast.c \
    $(SRC_DIR)lst/ft_lstadd_back.c \
    $(SRC_DIR)lst/ft_lstdelone.c \
    $(SRC_DIR)lst/ft_lstclear.c \
    $(SRC_DIR)lst/ft_lstiter.c \
    $(SRC_DIR)lst/ft_lstmap.c \
    \
    $(SRC_DIR)gnl/get_next_line_bonus.c \
    $(SRC_DIR)gnl/get_next_line_utils.c \
    $(SRC_DIR)gnl/get_next_line.c \
    \
    $(SRC_DIR)printf/ft_printf_base.c \
    $(SRC_DIR)printf/ft_printf_hexa.c \
    $(SRC_DIR)printf/ft_printf_ptr.c \
    $(SRC_DIR)printf/ft_printf_tools.c \
    $(SRC_DIR)printf/ft_printf_unsigned.c \
    $(SRC_DIR)printf/ft_printf.c

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(HEADER_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
	@echo "$(CYAN)Compiled $<$(NC)"

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Successful compilation of $(MAGENTA)libft$(NC)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
