# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/11 22:20:37 by fbafica           #+#    #+#              #
#    Updated: 2021/07/11 22:51:28 by fbafica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

C_SOURCES = get_next_line.c

C_PATH = ./source/

INCLUDES_PATH = ./includes/

OBJ = $(C_SOURCES:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ)
	@ar rcs $@ $^ 

$(OBJ): $(addprefix $(C_PATH), $(C_SOURCES))
	@gcc -c -I$(INCLUDES_PATH) $^ -Wall -Wextra -Werror -D BUFFER_SIZE=42

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all