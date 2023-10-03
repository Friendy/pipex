NAME = pipex
SRCS_SHARED = find_path.c get_args.c utils.c err_handler.c fds.c
SRCS = pipex.c
SRCS_B = pipex_bonus.c heredoc.c
LIBFT_A = libft/libft.a
#FLAGS = -Werror -Wall -Wextra
#ASFLAG = -fsanitize=leak
LFLAG = -LLeakSanitizer -llsan -lc++
OBJS = $(SRCS:.c=.o)
OBJS_SHARED = $(SRCS_SHARED:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all:$(NAME)

$(NAME): $(LIBFT_A) $(OBJS_SHARED) $(OBJS)
	cc -o $(NAME) $(ASFLAG) $(OBJS_SHARED) $(OBJS) -Llibft -lft $(LFLAG)

bonus: .bonus

.bonus: $(LIBFT_A) $(OBJS_SHARED) $(OBJS_B)
	@touch .bonus
	cc -o $(NAME) $(ASFLAG) $(OBJS_SHARED) $(OBJS_B) -Llibft -lft $(LFLAG)

$(OBJS_SHARED):
	cc $(FLAGS) -c $(ASFLAG) $(SRCS_SHARED)

$(OBJS):
	cc $(FLAGS) -c $(ASFLAG) $(SRCS)

$(OBJS_B):
	cc $(FLAGS) -c $(ASFLAG) $(SRCS_B)

$(LIBFT_A): make_libft

make_libft:
	make -C libft

clean:
	make fclean -C libft
	rm -f $(OBJS_SHARED) $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

rb: fclean bonus
	@rm -f .bonus

.PHONY: all clean fclean re rb