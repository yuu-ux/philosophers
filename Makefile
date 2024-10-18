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


FILES = main.c init.c utils.c validate.c thread_func.c create_thread.c
PHILO = philo.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRCS = $(addprefix ./src/, $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(PHILO)

$(PHILO): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRCS:.c=.o)

fclean: clean
	$(RM) $(PHILO)

re: fclean all

.PHONY : all clean fclean re
