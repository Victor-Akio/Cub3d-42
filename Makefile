# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 22:01:31 by vminomiy          #+#    #+#              #
#    Updated: 2020/08/30 00:27:24 by vminomiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC		=	clang

MODULES	=	$(LIB_DIR) $(MLX_DIR)

LIB_DIR	=	./libft

LIB		=	$(LIB_DIR)/libft.a

MLX_DIR	=	./minilibx-linux

MLX		=	$(MLX_DIR)/libmlx_Linux.a

CUB_DIR	=	./srcs

CC_FLAG =	-c		\
			-Wall	\
			-Wextra	\
			-Werror	\

INCLUDE	=	-I ./include	\
			-I $(MLX_DIR)	\
			-I $(LIB_DIR)

ML_FLAG	=	-L $(LIB_DIR)	\
			-L $(MLX_DIR)	\
			-lmlx_Linux		\
			-lXext			\
			-lX11			\
			-lm				\
			-lft			

RM		=	/bin/rm -f

CUB_SRC	=	$(CUB_DIR)/cub3d.c			\
			$(CUB_DIR)/error.c			\
			$(CUB_DIR)/file_manager.c	\
			$(CUB_DIR)/init.c			\
			$(CUB_DIR)/map_reader.c		\
			$(CUB_DIR)/map_utils.c		\
			$(CUB_DIR)/memfree.c		\
			$(CUB_DIR)/player.c			\
			$(CUB_DIR)/map.c			\
			$(CUB_DIR)/movement.c		\
			$(CUB_DIR)/keys.c			\
			$(CUB_DIR)/raycast.c		\
			$(CUB_DIR)/texture.c		\
			$(CUB_DIR)/mem_alloc.c		\
			$(CUB_DIR)/bmp.c			\
			$(CUB_DIR)/cub_utils.c		\
			$(CUB_DIR)/sprite.c

SRC		=	$(CUB_SRC)

OBJ		=	$(patsubst %.c, %.o, ${SRC})

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(LIB) $(MLX)
			$(CC) -fsanitize=address $(ML_FLAG) -o $@ $^

%.o		:	%.c
			$(CC) -g $(CC_FLAG) $(INCLUDE) $< -o $@

$(LIB)	:
			$(MAKE) -C $(LIB_DIR)

$(MLX)	:
			$(MAKE) -C $(MLX_DIR)

clean	:
			for dir in $(MODULES); do	\
				$(MAKE) clean -C $$dir;	\
			done
			$(RM) $(OBJ)

fclean	:	clean
			$(MAKE) fclean -C $(LIB_DIR)
			$(RM) $(NAME)

re		:	fclean all