# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 15:02:44 by maheleni          #+#    #+#              #
#    Updated: 2024/06/09 15:02:46 by maheleni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = libft/libft.a

LIBFT_MAKEFILE = libft/Makefile

LIBFT_DIR = libft

SRCS = mod_split.c \
	pipex.c \
	check_args.c


OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) clean
	
re: fclean all

.PHONY: all clean fclean re
