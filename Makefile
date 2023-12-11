CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

FRM = rm -rf

NAME = Webserv

HEADER =	includes/CGI.hpp\
            includes/Parsing.hpp\
            includes/Request.hpp\
            includes/Server.hpp\
            includes/Webserv.hpp\

SRC =	SRC/main.cpp\
        SRC/Fiddler/final_server.cpp \
        SRC/Buda/Buda.cpp \
        SRC/Buda/finalParsing.cpp \
        SRC/Buda/cgi.cpp \
        SRC/Buda/string_utils.cpp \
        SRC/Buda/webserv.cpp \
        SRC/Cheesy/extraFunctions.cpp \
        SRC/Cheesy/DELETE/DELETE.cpp \
        SRC/Cheesy/GET/Get.cpp \
        SRC/Cheesy/POST/POST.cpp \
        SRC/Cheesy/POST/Boundry.cpp \
        SRC/Cheesy/POST/Chunked.cpp \
        SRC/Cheesy/Request/CheckLocation.cpp \
        SRC/Cheesy/Request/Request.cpp \
        SRC/Cheesy/Request/InitRequest.cpp \
        SRC/Cheesy/Response/Response.cpp \

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

${NAME} : $(OBJ) $(HEADER)
	${CC} $(CFLAGS) ${OBJ} -o $(NAME)

%.o : %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(FRM) ${OBJ}

fclean: clean
	$(FRM) ${NAME}

re: fclean all

fuck:  fclean
	$(FRM) Webserv.dSYM .vscode
    
