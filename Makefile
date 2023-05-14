NAME = pipex
SRCS = pipex.c find_path.c get_args.c utils.c
LIBFT_A = libft/libft.a
FLAGS = -Werror -Wall -Wextra
OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(LIBFT_A) $(OBJS) 
	cc -o $(NAME) $(OBJS) -Llibft -lft

$(OBJS):
	cc -c $(SRCS)

$(LIBFT_A): make_libft

make_libft:
	make -C libft

clean:
	#make fclean -C libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all