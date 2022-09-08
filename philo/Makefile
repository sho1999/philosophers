# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 09:35:52 by smuramat          #+#    #+#              #
#    Updated: 2022/09/08 12:24:56 by smuramat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_NAME = $(shell echo *.c)

OBJS = ${SRC_NAME:.c=.o}

CC = cc -pthread

CFLAGS = -Wall	-Wextra	-Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re