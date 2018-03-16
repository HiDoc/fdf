# PATH :
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/ \
		   ./minilibx/ \
		   ./libft/includes/

NAME = fdf

# MAKE VAR :
CC = gcc -g
CFLAGS = -Werror -Wextra -Wall

# SNIPPETS :
complete = @echo "\033[92mComplete\033[0m"
cleaning = @echo "\033[36mCleaning complete\033[0m"
ok = [\033[92mOK\033[0m]

SRC_NAME = main.c \
		   get_next_line.c \
		   fdf_color.c \
		   fdf_draw.c \
		   fdf_grid.c \
		   fdf_keyhook.c \
		   fdf_maths.c \
		   fdf_max.c \
		   fdf_parsing.c \
		   fdf_point.c \
		   fdf_utils.c \
		   fdf_fdf.c

OBJ_NAME = $(SRC_NAME:.c=.o)

# PREFIXES
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

LIB = -L ./minilibx -L ./libft -lftprintf -lmlx 

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "*****************************************************"
	@echo "Launching Makefile for Libft.."
	@make -C ./libft -j 5
	@echo "*****************************************************"
	@echo "Building fdf.."
	@echo "$(ok)  Compiling sources into a program.."
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -framework OpenGL -framework AppKit -o $(NAME) $(LIB)
	@echo "*****************************************************"
	@echo "Your fdf is ready to run !"

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "[\033[92m..\033[0m] Compiling $< into object file.."
	@tput cuu1;tput el;
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "$(ok)  Compiling $< into object file.."

clean: 
	@echo "*****************************************************"
	@echo "Cleaning process for Libft engaged.."
	@make clean -C ./libft
	$(cleaning)
	@echo "*****************************************************"
	@echo "Cleaning process for fdf engaged.."
	@echo "Removing fdf binaries.."
	@rm -rf $(OBJ)
	$(cleaning)
	@echo "*****************************************************"

fclean: clean
	@echo "Cleaning library and program.."
	@echo "Removing program named fdf.."
	@rm -f $(NAME)
	@make fclean -C ./libft
	$(cleaning)
	@echo "*****************************************************"

re: fclean all
