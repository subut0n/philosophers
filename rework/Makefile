# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 13:33:20 by addzikow          #+#    #+#              #
#    Updated: 2021/11/08 14:05:10 by addzikow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME	= philo
LIB		= libft
SRCS	= philo.c
HEAD	= libft/libft.a
OBJ		= $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror
CC 		= gcc

all: $(NAME)

$(NAME):
	make -C $(LIB)
	$(CC) $(FLAGS) $(SRCS) $(HEAD) 

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean all