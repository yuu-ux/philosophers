# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehara <yehara@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 13:31:55 by yehara            #+#    #+#              #
#    Updated: 2024/10/02 20:08:20 by ebarayuug        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.c

NAME = philosophers.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRCS:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
