NAME = containers_ft

NAME_STD = containers_std

SOURCE = test.cpp tests/vector_test.cpp tests/stack_test.cpp tests/map_test.cpp tests/set_test.cpp

HDR = tests/test.hpp vector.hpp stack.hpp map.hpp set.hpp

FLAGS = -Wall -Wextra -Werror --std=c++98

OBJ = $(SOURCE:.cpp=.o)

OBJ_STD = $(addsuffix _std.o, $(basename $(SOURCE)))

all: $(NAME) $(NAME_STD)

$(NAME): $(OBJ)
	@clang++ $(OBJ) -o $(NAME)

$(NAME_STD): $(OBJ_STD)
	@clang++ $(OBJ_STD) -o $(NAME_STD)

%.o:%.cpp $(HDR)
	@clang++ -c $(FLAGS) $< -o $@

%_std.o:%.cpp $(HDR)
	@clang++ -c $(FLAGS) $< -o $@ -D STD

clean:
	@rm -rf $(OBJ) $(OBJ_STD)

fclean: clean
	@rm -rf $(NAME) $(NAME_STD)

re: fclean all
