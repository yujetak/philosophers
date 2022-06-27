# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 09:45:42 by yotak             #+#    #+#              #
#    Updated: 2022/06/27 09:54:45 by yotak            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
CFLAGS	+=	-fsanitize=thread -g3
endif
RM		=	rm -rf

WHITE	=	\033[0m
BLUE	=	\033[0;34m
RED		=	\033[0;91m
GREEN	=	\033[0;92m

SRCS	=	philo.c \
			philo_utils.c \
			philo_utils2.c \
			check_arg.c \
			check_arg_utils.c \
			struct_info.c \
			set_info.c \
			run_philo.c \
			free.c \

DIR_OBJ	=	./obj
OBJS	=	$(SRCS:%.c=$(DIR_OBJ)/%.o)

all		:	make_objd $(NAME)

make_objd :
			@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : %.c
			@$(CC) $(CFLAGS) -c $< -o $@

# cc -Wall -Wextra -Werror -o 실행파일명 목적파일들
$(NAME)	:	$(OBJS)
			@$(CC) $(CFLAGS) -o $@ $^
			@echo "$(BLUE)🪄 CFLAGS = $(CFLAGS)$(WHITE)"
			@echo "$(GREEN)💡 executable $(NAME) created$(WHITE)"

clean	:
			@$(RM) $(DIR_OBJ)

fclean	:
			@$(MAKE) clean
			@$(RM) $(NAME)
			@echo "$(RED)🪚 deleted $(NAME)$(WHITE)"

re		:
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY	: all clean fclean re


