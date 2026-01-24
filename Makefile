# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 16:20:34 by aelbouaz          #+#    #+#              #
#    Updated: 2025/10/02 16:10:20 by aelbouaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = cc

CUBED = cubed
CUBED_SRCS = main.c initialise_map.c utils_1.c

CUBED_OBJ = $(CUBED_SRCS:.c=.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX42_DIR = mlx42
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

$(CUBED): $(LIBFT) $(CUBED_OBJ) $(MLX42_LIB) 
	@$(CC) $(CFLAGS) -o $(CUBED) $(CUBED_OBJ) \
	-L$(LIBFT_DIR) -lft \
	$(MLX42_LIB) -I$(MLX42_INC) -ldl -lglfw -pthread -lm

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX42_INC) -c $< -o $@
	@printf "$(GREEN).$(RESET)"

clean:
	@printf "$(BLUE)Cleaned Up$(RESET)\n"
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build
	@rm -f $(CUBED_OBJ)

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(CUBED)

re: fclean all

.PHONY: all clean fclean re
