# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#    Updated: 2016/05/21 20:38:34 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c ./src

SRC = cd.c \
	  env.c \
	  env_tab.c \
	  error.c \
	  exec_bin.c \
	  exit.c \
	  free.c \
	  handle_env.c \
	  handle_sig.c \
	  main.c \
	  parse.c \
	  prompt_display.c \
	  pwd_update.c \
	  setenv.c \
	  str_tools.c \
	  unsetenv.c

NAME = minishell

FLAGS = -Wall -Werror -Wextra

LIBDIR = ./libft/

INCLUDES = $(LIBDIR)includes/

LIB = $(LIBDIR)libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
		gcc -g $(FLAGS) $(OBJ) -L$(LIBDIR) -lft -o $@

$(LIB):
	make -C $(LIBDIR)

%.o: %.c
	gcc -g $(FLAGS) -c $< -I . -I $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
