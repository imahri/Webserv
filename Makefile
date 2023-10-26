# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imahri <imahri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 13:42:42 by imahri            #+#    #+#              #
#    Updated: 2023/10/26 15:30:36 by imahri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

HEADER =	includes/webserv.hpp \
			includes/color.hpp \

SRC =	main\

OBJDIR = OBJDIR/

OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(SRC)))

all : ${OBJDIR} ${NAME}

${OBJDIR}:
	@mkdir -p $(OBJDIR)

${NAME} : $(OBJ) $(HEADER)
	@${CC} $(FLAGS) ${OBJ} -o $(NAME)

$(OBJDIR)%.o : %.cpp $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo " _       ____________ _____ __________ _    __"
	@echo "| |     / / ____/ __ ) ___// ____/ __ \ |  / /"
	@echo "| | /| / / __/ / __  \__ \/ __/ / /_/ / | / / "
	@echo "| |/ |/ / /___/ /_/ /__/ / /___/ _, _/| |/ /  "
	@echo "|__/|__/_____/_____/____/_____/_/ |_| |___/   "

clean :
	@rm -rf $(OBJDIR)
	@echo "    ____  ____  _   ________"
	@echo "   / __ \/ __ \/ | / / ____/"
	@echo "  / / / / / / /  |/ / __/   "
	@echo " / /_/ / /_/ / /|  / /___   "
	@echo "/_____/\____/_/ |_/_____/   "

fclean : clean
	@rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re