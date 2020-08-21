# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 22:01:31 by vminomiy          #+#    #+#              #
#    Updated: 2020/08/21 08:31:49 by vminomiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FRM_LINUX = -lXext -lX11 -lbsd -lm
#FRM_MAC = -framework OpenGL -framework AppKit

INCLUDES = -I $(MLX_PATH) -I $(LIBFT_PATH)

MLX = -L $(MLX_PATH) -lmlx
MLX_PATH = ./minilibx-linux

LIBFT = -L $(LIBFT_PATH) -lft
LIBFT_PATH = ./libft

FLAGS =		-Wall -Wextra -Werror -fsanitize=address

SRCS =		cub3d.c \
			file_manager.c \
			init.c \
			map_reader.c \
			mapa.c \
			memfree.c \
			error.c \
			player.c \
			mapa_utils.c \

OBJS =		$(patsubst %.c, %.o, $(SRCS))

$(NAME) :	$(OBJS)
			#Cub3d Compile
			@clang -g $(FLAGS) $(FRM_LINUX) $(OBJS) $(INCLUDES) $(MLX) $(LIBFT) -o $(NAME)

all :		$(NAME)

clean :
			rm -f $(OBJS)

fclean :	clean
			rm -f $(NAME)

re :		fclean all