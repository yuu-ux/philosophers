# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehara <yehara@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 13:31:55 by yehara            #+#    #+#              #
#    Updated: 2024/11/04 21:21:58 by yehara           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FILES = main.c init.c utils.c validate.c thread_func.c create_thread.c monitor.c
PHILO = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=thread
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
