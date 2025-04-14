# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 10:34:57 by jpiensal          #+#    #+#              #
#    Updated: 2025/04/14 17:11:25 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philosophers
CFLAGS		= -Werror -Wall -Wextra

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

