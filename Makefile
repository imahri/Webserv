# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:42:42 by imahri            #+#    #+#              #
#    Updated: 2023/11/23 14:51:24 by eamghar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

FRM = rm -rf

NAME = Webserv

HEADER = includes/*.hpp\

SRC =	SRC/*.cpp \
		SRC/Fiddler/*.cpp \
		SRC/Buda/*.cpp \
		SRC/Cheesy/*.cpp \
		SRC/Cheesy/DELETE/*.cpp \
		SRC/Cheesy/GET/*.cpp \
		SRC/Cheesy/POST/*.cpp \
		SRC/Cheesy/REQUEST/*.cpp \
		SRC/Cheesy/RESPONSE/*.cpp \
		SRC/Cheesy/SENDFILE/*.cpp \

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) 

clean:
	$(FRM) $(NAME)

fclean: clean

re: fclean all


fuck: 
	$(FRM) Webserv.dSYM
	