# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 19:18:45 by mrubina           #+#    #+#              #
#    Updated: 2023/04/30 17:30:40 by mrubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
	ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
	ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c\
	get_next_line.c get_next_line_utils.c ft_printf.c
#SRCS_PRINTF = 
#align_params.c extract_params.c utils.c variants.c width.c
SRCS_PRINTF_U =  print_arg.c \
shortcuts.c convert_to_hex.c convert.c int_putnbr.c int_put.c get_arg.c
OBJS = $(SRCS:.c=.o)
OBJS_PRINTF_U = $(SRCS_PRINTF_U:.c=.o)
FLAGS  = -Wall -Werror -Wextra

all:$(NAME)

$(NAME): $(OBJS_PRINTF_U) $(OBJS)
	ar rc $(NAME) $(OBJS) $(OBJS_PRINTF_U)

$(OBJS):
	cc $(FLAGS) -c $(SRCS)

$(OBJS_PRINTF_U):
	cc $(FLAGS) -c $(addprefix printf_utils/, $(SRCS_PRINTF_U))

clean:
	rm -f $(OBJS) $(OBJS_PRINTF_U)

fclean: clean
	rm -f $(NAME)

re: fclean all
