# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 10:34:57 by jpiensal          #+#    #+#              #
#    Updated: 2025/05/13 12:04:37 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CFLAGS		= -Werror -Wall -Wextra -I.
OBJ_PATH	= obj/
SRC			= main.c philosophers_utils.c init.c \
			  philosophers.c observer.c \
			  actions.c prints.c threads.c mutex.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)
HEADER		= ./philosophers.h

all:		$(NAME)

$(NAME):	$(OBJ_PATH) $(OBJ) $(HEADER)
			cc $(OBJ) -o $(NAME)

$(OBJ):		$(OBJ_PATH)%.o: %.c
			cc $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
			@mkdir -p $(OBJ_PATH)

clean:
			@rm -rf $(OBJ_PATH)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

