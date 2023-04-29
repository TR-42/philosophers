# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 22:24:52 by kfujita           #+#    #+#              #
#    Updated: 2023/04/30 01:34:39 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC_DIR	=	./srcs

SRCS_MAIN	=\
	main.c\

SRCS	=\
	libft/can_add.c\
	libft/can_mul.c\
	libft/ft_atop.c\
	libft/ft_calloc.c\
	libft/ft_is.c\
	libft/ft_strlen.c\
	libft/ft_swap.c\
	libft/ft_ultoa.c\
	errors.c\
	manager.c\
	print_log.c\
	simulator.c\
	sleeper.c\

OBJ_DIR	=	./obj
OBJS_NOMAIN	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS	=	$(OBJS_NOMAIN) $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))

DEPS	=	$(OBJS:.o=.d)

override CFLAGS	+=	-Wall -Wextra -Werror -MMD -MP
INCLUDES	=	-I ./headers

CC		=	cc

TEST_DIR	=	.tests
TEST_SLEEPER	=	test_sleeper
TEST_T_TV_ADDMS	=	test_t_tv_addms
TEST_T_TV_ISPASSED	=	test_t_tv_ispassed

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -lpthread $(INCLUDES) -o $@ $^

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
	rm -d $(OBJ_DIR)/libft 2>/dev/null || exit 0
	rm -d $(OBJ_DIR) 2>/dev/null || exit 0

fclean:	clean
	rm -f $(NAME)

re:	fclean all

t: test
test:\
	$(OBJ_DIR)/$(TEST_SLEEPER)\
	$(OBJ_DIR)/$(TEST_T_TV_ADDMS)\
	$(OBJ_DIR)/$(TEST_T_TV_ISPASSED)\

	@echo '~~~~~~~~~~ TEST ~~~~~~~~~~~~'
	@$(OBJ_DIR)/$(TEST_T_TV_ADDMS)

	@echo
	@$(OBJ_DIR)/$(TEST_T_TV_ISPASSED)

	@echo
	@$(OBJ_DIR)/$(TEST_SLEEPER)

$(OBJ_DIR)/$(TEST_SLEEPER): ./$(TEST_DIR)/$(TEST_SLEEPER).c $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) -lpthread $(INCLUDES) -o $@ $^

$(OBJ_DIR)/$(TEST_T_TV_ADDMS): ./$(TEST_DIR)/$(TEST_T_TV_ADDMS).c $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) -lpthread $(INCLUDES) -o $@ $^

$(OBJ_DIR)/$(TEST_T_TV_ISPASSED): ./$(TEST_DIR)/$(TEST_T_TV_ISPASSED).c $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) -lpthread $(INCLUDES) -o $@ $^

-include $(DEPS) $(DEPS_BONUS)

.PHONY:	clean debug test
