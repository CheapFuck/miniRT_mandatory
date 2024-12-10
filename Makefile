NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -flto -I./includes -I./MLX42/include
# MLX_FLAGS = -L./MLX42/build -lmlx42 -ldl -lglfw -pthread -lm
# --suppressions="mlx42.supp" 
MLX_FLAGS = -L./MLX42/build -lmlx42 -ldl -lglfw -lm
LIBFTDIR 		:=	libft/
LIBMLX	:= ./MLX42
INCLUDE			:=	-L libft -lft


SRC = src/main.c \
      src/render/render.c \
	  src/render/render1.c \
	  src/render/render2.c \
      src/render/intersection.c \
	  src/render/intersection1.c \
      src/render/lighting.c \
	  src/render/lighting1.c \
      src/utils.c \
	  src/utils1.c \
	  src/parser/parse_camera.c \
	  src/parser/parse_file.c \
	  src/parser/parse_light.c \
  	  src/parser/parse_plane.c \
	  src/parser/parse_cylinder.c \
	  src/parser/parse_cylinder1.c \
  	  src/parser/parse_sphere.c \
	  
OBJ = $(SRC:.c=.o)

all: libmlx $(NAME)


libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME) $(INCLUDE) 

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf miniRT

re: fclean all
