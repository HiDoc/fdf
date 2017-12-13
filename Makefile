SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/ \
		   ./minilibx/ \
		   ./libft/includes/

NAME = fdf
CC = gcc -g
CFLAGS = -Werror -Wextra -Wall

complete = @echo "\033[92mComplete\033[0m"
cleaning = @echo "\033[36mCleaning complete\033[0m"

SRC_NAME = main.c \
		   get_next_line.c \
		   parsing.c \
		   ft_point.c \
		   ft_draw.c \
		   ft_grid.c \
		   ft_maths.c \
		   ft_utils.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))
LIB = -L ./libft -lft -L ./minilibx -lmlx

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[33mLaunching Makefile for Libft..\033[0m"
	@make -C ./libft
	@echo "**************************************"
	@echo "\033[33mBuilding fdf..\033[0m"
	@echo "Compiling sources into a program.."
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) $(INC) -framework OpenGL -framework AppKit -o $(NAME)
	$(complete)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "Compilating files into binaries.."
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@echo "**************************************"
	@echo "\033[33mCleaning process for Libft engaged..\033[0m"
	@make clean -C ./libft
	$(cleaning)
	@echo "**************************************"
	@echo "\033[33mCleaning process for fdf engaged..\033[0m"
	@echo "Removing fdf binaries.."
	@rm -f $(OBJ)
	$(cleaning)

fclean: clean
	@echo "\033[33mCleaning library and program..\033[0m"
	@echo "Removing program named fdf.."
	@rm -f $(NAME)
	@make fclean -C ./libft
	$(cleaning)
	@echo "**************************************"

debug: all
	lldb ./fdf ./maps/elem.fdf
re: fclean all
