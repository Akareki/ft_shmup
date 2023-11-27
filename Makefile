# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 15:09:57 by aoizel            #+#    #+#              #
#    Updated: 2023/11/26 15:16:49 by aoizel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 			=	ft_shmup

CFLAGS 			=	-Wall -Wextra -Werror

CC 				=	cc $(CFLAGS)

SOURCES 		=	ft_shmup.c background.c main.c	

OBJECTS 		=	$(SOURCES:.c=.o)

DEPENDENCIES	=	ft_shmup.h	


all:		$(NAME) 

$(NAME):	$(OBJECTS)
				$(CC) $(OBJECTS) -o $(NAME) -lncurses

%.o:		%.c $(DEPENDENCIES)
				$(CC) -c -I. $< -lncurses

clean:
				rm -rf $(OBJECTS)

fclean:		clean
				rm -rf $(NAME)

re:			fclean 
				make all

.PHONY: 	all clean fclean re
