# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 16:20:34 by aelbouaz          #+#    #+#              #
#    Updated: 2026/07/14 15:49:42 by aelbouaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -MMD
CC = cc

CUBED = cub3D
CUBED_SRCS = Main.c Parsing/error_check.c Parsing/get_colors.c \
			Parsing/get_textures.c Parsing/gnl.c Parsing/initialise_map.c \
			Parsing/utils_1.c Parsing/update_map.c Parsing/texture_color_check.c \
			Map_validity/Map_validity.c Map_validity/Components_exist.c \
			Map_validity/Flood_fill.c Plane/make_plane.c \
			Rendering/rendering.c Rendering/raycasting.c Game_Dev/weapon_textures.c \
			Game_Dev/weapons_animation.c Game_Dev/weapons_animation_utils.c \
			Game_Dev/Movements.c Game_Dev/Rotations.c Enemy/enemy.c \
			Game_Dev/Doors.c

OBJS_DIR = Objects
CUBED_OBJ = $(addprefix $(OBJS_DIR)/, $(CUBED_SRCS:.c=.o))

DEPS = ${CUBED_OBJ:.o=.d}

LIBFT_DIR = Libraries/Libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX42_DIR = Libraries/Mlx42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
MLX42_INC = $(MLX42_DIR)/include

HEADERS = $(LIBFT_DIR)libft.h $(MLX42_INC)/MLX42/MLX42.h

GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m


all: $(MLX42_LIB) $(LIBFT) $(CUBED)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX42_LIB):
	@printf "$(GREEN)Compiling MLX42$(RESET)"
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR) > /dev/null
	@make -s -C $(MLX42_DIR)/build | while read -r line; do printf "$(GREEN).$(RESET)"; done

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(CUBED): $(MLX42_LIB) $(LIBFT) $(CUBED_OBJ)
	@$(CC) $(CFLAGS) -o $(CUBED) $(CUBED_OBJ) \
	-L $(LIBFT_DIR) -lft \
	$(MLX42_LIB) -I$(MLX42_INC) -ldl -lglfw -pthread -lm

$(OBJS_DIR)/%.o: %.c $(HEADERS) Makefile | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX42_INC) -c $< -o $@
	@printf "$(GREEN).$(RESET)"

clean:
	@printf "$(BLUE)Cleaned Up$(RESET)\n"
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(CUBED)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
