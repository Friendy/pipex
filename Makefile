NAME = pipex
SRCS = pipex.c find_path.c get_args.c utils.c err_handler.c fds.c
SRCS_B = pipex_bonus.c find_path.c get_args.c utils.c err_handler.c fds_bonus.c
LIBFT_A = libft/libft.a
#FLAGS = -Werror -Wall -Wextra
ASFLAG = -fsanitize=address
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all:$(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	cc -o $(NAME) $(ASFLAG) $(OBJS) -Llibft -lft

$(OBJS):
	cc $(FLAGS) -c $(ASFLAG) $(SRCS)

bonus: $(LIBFT_A) $(OBJS_B)
	cc -o $(NAME) $(ASFLAG) $(OBJS_B) -Llibft -lft

$(OBJS_B):
	cc $(FLAGS) -c $(ASFLAG) $(SRCS_B)

$(LIBFT_A): make_libft

make_libft:
	make -C libft

clean:
	make fclean -C libft
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

rb: fclean bonus

.PHONY: all clean fclean re