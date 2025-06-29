CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++98

OBJDIR = obj

SOURCES = main.cpp \
          commands.cpp \
          Pass.cpp

OBJS = $(SOURCES:.cpp=.o)

NAME = ircserv
INCS = all.hpp \
       commands.hpp \
       Pass.hpp

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(INCS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re