# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 22:24:52 by kfujita           #+#    #+#              #
#    Updated: 2023/04/21 23:51:37 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC_DIR	=	./srcs

SRCS	=\
	libft/ft_strlen.c\

OBJ_DIR	=	./obj
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

DEPS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.d))

override CFLAGS	+=	-Wall -Wextra -Werror -MMD -MP
INCLUDES	=	-I ./headers

CC		=	cc

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/libft
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

debug: clean
	make CFLAGS=-DDEBUG

bonus:
	make $(NAME_BONUS)

clean:
	rm -f $(OBJS) $(DEPS)
	rm -d $(OBJ_DIR) 2>/dev/null || exit 0

fclean:	clean
	rm -f $(NAME)

re:	fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY:	clean debug
