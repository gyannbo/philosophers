# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:34:40 by gbonis            #+#    #+#              #
#    Updated: 2024/09/05 15:34:43 by gbonis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	checker_thread.c\
		death.c\
		free.c\
		ft_atoi_overflow.c\
		init_arrays.c\
		init_threads_structs.c\
		loops.c\
		main.c\
		mutex.c\
		pick_loser_func.c\
		smart_sleep.c\
		thread_eat.c\
		thread_loop.c\
		threads_init.c\
		time.c\
		unlock_mutexes.c\
		wrong_args.c\

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = include/

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

NAME = philo

all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR): 
	mkdir obj

clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all 

.PHONY: all clean fclean re bonus
