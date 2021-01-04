# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 12:41:57 by dnakano           #+#    #+#              #
#    Updated: 2021/01/04 09:36:07 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
NAME		:=	philo_two
SRCS		:=	main.c \
				philo_store_argv.c \
				philo_has_finished.c \
				philo_putstatus.c \
				philo_puterr_and_return.c \
				ft_atol.c \
				ft_isdigit.c \
				ft_isspace.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				philo_init.c \
				philo_activity.c \
				philo_eat.c \
				philo_sleep.c \
				philo_check_dead.c \
				philo_free_ret.c \
				philo_gettime.c \
				philo_sem_utils.c
OBJS		:=	$(SRCS:%.c=%.o)
HEADERS		:=	philo_two.h \
				philo_utils.h
HEADERDIR	:=	.

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
				$(CC) $(OBJS) $(addprefix -I,$(HEADERDIR)) -o $(NAME)

.c.o:
				$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

.PHONY:			clean
clean:
				rm -f $(OBJS)

.PHONY:			fclean
fclean:			clean
				rm -f $(NAME)

.PHONY:			re
re:				fclean all
