NAME = containers

SOURCE = tests/test.cpp tests/vector_test.cpp tests/stack_test.cpp tests/map_test.cpp tests/set_test.cpp
# SOURCE = main.cpp

OBJ_DIR = .obj

HDR = test.hpp vector.hpp stack.hpp map.hpp set.hpp

FLAGS = -Wall -Wextra -Werror --std=c++98

OBJ = $(addprefix $(OBJ_DIR)/,$(SOURCE:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@clang++ $(SOURCE) -o $(NAME)

$(OBJ_DIR)/%.o:%.cpp $(HDR)
	@mkdir -p $(OBJ_DIR)
	@clang++ -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
