# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 10:34:57 by jpiensal          #+#    #+#              #
#    Updated: 2025/04/23 15:11:04 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CFLAGS		= -Werror -Wall -Wextra -g

OBJ_PATH	= obj/
SRC			= main.c philosophers_utils.c \
			  philosophers.c \
			  actions.c prints.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

all:		$(NAME)

$(NAME):	$(OBJ_PATH) $(OBJ)
			cc $(OBJ) -o $(NAME)

$(OBJ):		$(OBJ_PATH)%.o: %.c
			cc $(CFLAGS) -c $< -o $@ -I.

$(OBJ_PATH):
			@mkdir -p $(OBJ_PATH)

#debug:		fclean $(OBJ_PATH)%.o: %.c
#			cc $(DEBUG_FLAG) -c $< -o $@ -I

clean:
			@rm -rf $(OBJ_PATH)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

