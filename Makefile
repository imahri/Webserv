# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:42:42 by imahri            #+#    #+#              #
#    Updated: 2023/11/27 11:29:33 by eamghar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

FRM = rm -rf

NAME = Webserv

HEADER = includes/*.hpp\

SRC = 	SRC/main.cpp\
		SRC/Fiddler/final_server.cpp \
		SRC/Fiddler/oldServer.cpp \
		SRC/Buda/Buda.cpp \
		SRC/Buda/finalParsing.cpp \
		SRC/Buda/string_utils.cpp \
		SRC/Buda/webserv.cpp \
		SRC/Cheesy/extraFunctions.cpp \
		SRC/Cheesy/DELETE/DELETE.cpp \
		SRC/Cheesy/GET/Get.cpp \
		SRC/Cheesy/POST/POST.cpp \
		SRC/Cheesy/Request/CheckLocation.cpp \
		SRC/Cheesy/Request/Request.cpp \
		SRC/Cheesy/Request/InitRequest.cpp \
		SRC/Cheesy/Response/Response.cpp \
		SRC/Cheesy/SENDFILE/sendFile.cpp \

		
all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) 

clean:
	$(FRM) $(NAME)

fclean: clean

re: fclean all


fuck:  fclean
	$(FRM) Webserv.dSYM .vscode
	
nik : fclean fuck re
	