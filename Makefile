.PHONY: clean, fclean, re, all

.SUFFIXES:

NAME = FdF

SRC 	= 		main.c \
				mlx.c \
				calculs.c \
				draw.c \
				hook.c \
				parsing.c \
				check.c \
				move_options.c

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX = ./minilibx_macos/
MLX_LIB = $(addprefix $(MLX),mlx.a))
MLX_INC = -I ./minilibx_macos
MLX_LNK = -L ./minilibx_macos -l mlx -framework OpenGl -framework AppKit

FT = ./libft/
FT_LIB = $(addprefix $(FT),libft.a))
FT_INC = -I ./libft
FT_LNK = -L ./libft -l ft

SRCDIR = ./src/
INCDIR = ./includes/
OBJDIR = ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj: 
		mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
		$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
		make -C $(FT)

$(MLX_LIB):
		make -C $(MLX)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	
clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	

re: fclean all
