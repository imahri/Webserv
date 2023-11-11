# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:42:42 by imahri            #+#    #+#              #
#    Updated: 2023/11/11 12:29:37 by eamghar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

FLAGS = -g -fsanitize=address # -Wall -Wextra -Werror -std=c++98 

HEADER =    includes/webserv.hpp \
			includes/color.hpp \

SRC =	main\
		string_utils\

OBJDIR = OBJDIR/

FRM = rm -rf

NAME = Webserv

HEADER = *.hpp\

SRC =	*.cpp\

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(FRM) $(NAME)

fclean: clean

re: fclean all
