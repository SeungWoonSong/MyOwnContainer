# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susong <susong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 09:25:35 by susong            #+#    #+#              #
#    Updated: 2023/02/27 17:12:54 by susong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	container

SOURCE		=	test.cpp

OBJECT		=	$(SOURCE:.cpp=.o)

COMPILE		= 	c++

FLAGS		= 	-Wall -Wextra -Werror -std=c++98


all: $(NAME)

%.o: %.cpp
	$(COMPILE) $(FLAGS) -c $< -o $@

$(NAME): $(OBJECT)
	$(COMPILE) $(FLAGS) $(OBJECT) -o $(NAME)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
