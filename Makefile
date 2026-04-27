NAME		= libasm.a
CC			= cc
NASM		= nasm
NASMFLAGS	= -f macho64
ARCH		= x86_64
CFLAGS		= -Wall -Wextra -Werror -arch $(ARCH)
LDFLAGS		= -arch $(ARCH)

ASM_SRCS	= ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
ASM_OBJS	= $(ASM_SRCS:.s=.o)
BONUS_SRCS	= ft_atoi_base_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s \
			  ft_list_sort_bonus.s ft_list_remove_if_bonus.s
BONUS_OBJS	= $(BONUS_SRCS:.s=.o)

TEST_NAME	= test_libasm
TEST_SRC	= main.c
TEST_BONUS_NAME = test_libasm_bonus
TEST_BONUS_SRC = main_bonus.c

all: $(NAME)

$(NAME): $(ASM_OBJS)
	ar rcs $(NAME) $(ASM_OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(TEST_NAME): $(NAME) $(TEST_SRC) libasm.h
	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) $(LDFLAGS) -o $(TEST_NAME)

test: $(TEST_NAME)

$(TEST_BONUS_NAME): bonus $(TEST_BONUS_SRC) libasm_bonus.h
	$(CC) $(CFLAGS) $(TEST_BONUS_SRC) $(NAME) $(LDFLAGS) -o $(TEST_BONUS_NAME)

test_bonus: $(TEST_BONUS_NAME)

clean:
	rm -f $(ASM_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME) $(TEST_BONUS_NAME)

re: fclean all

bonus: $(ASM_OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(ASM_OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus test test_bonus
