# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yotak <yotak@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 09:45:42 by yotak             #+#    #+#              #
#    Updated: 2022/06/20 16:04:31 by yotak            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g

RM		=	rm -rf

SRCS	=	philo.c \
			check_arg.c \
			check_arg_utils.c \
			struct_info.c \
			struct_philosopher.c \
			run_philo.c \
			free.c \

DIR_OBJ	=	./obj
OBJS	=	$(SRCS:%.c=$(DIR_OBJ)/%.o)

all		:	make_objd $(NAME)

make_objd :
			mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

# cc -Wall -Wextra -Werror -o 실행파일명 목적파일들
$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^
			@echo "\033[0;92m📌 executable $(NAME) created\033[0m"

clean	:
			$(RM) $(DIR_OBJ)

fclean	:	
			$(MAKE) clean
			$(RM) $(NAME)
			@echo "\033[0;91m📌 deleted $(NAME)\033[0m"

re		:
			$(MAKE) fclean
			$(MAKE) all

.PHONY	: all clean fclean re


