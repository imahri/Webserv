# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imahri <imahri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:42:42 by imahri            #+#    #+#              #
#    Updated: 2023/11/11 23:28:24 by imahri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98

FRM = rm -rf

NAME = Webserv

HEADER = includes/*.hpp\

SRC =	SRC/*.cpp\

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(FRM) $(NAME)

fclean: clean

re: fclean all