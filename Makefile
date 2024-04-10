# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romain <romain@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 14:30:15 by romain            #+#    #+#              #
#    Updated: 2024/04/10 15:10:06 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES 		=	main.c \
					
SRC_DIR 		= srcs
OBJ_DIR 		= objs
SRC 			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ 			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJ_debug		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=_debug.o))
HEADER_DIR 		= includes
LIBFT			= libft/libft.a
CC				= cc
CFLAGS 			= -Wextra -Wall -Werror
Xext 			= /opt/homebrew/Cellar/libxext/1.3.5/lib
X11 			= /opt/homebrew/Cellar/libx11/1.8.7/lib
NAME			= cube3d
NAME_debug		= cube3d_debug
MINILIBX		= minilibx-linux/libmlx.a
LIBS			= -L$(Xext) -L$(X11) -lX11 -lXext -L$(dir $(MINILIBX)) -lmlx

all: $(NAME)

db: $(NAME_debug)


$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g3 -I$(HEADER_DIR) -L$(Xext) -lXext -L$(X11) -lX11 -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) $(LIBS) -I$(HEADER_DIR) -c $< -o $@

$(NAME): $(OBJ) $(MINILIBX) $(LIBFT) $(MINIGNL)
	$(CC) $(CFLAGS)  $^ -o $@

$(NAME_debug): $(OBJ_debug) $(MINILIBX) $(LIBFT) $(MINIGNL)
	$(CC) $(CFLAGS) $(LIBS) -I$(HEADER_DIR) -c $< -o $@

$(MINILIBX):
	Make -C $(dir $@)

$(LIBFT):
	make -C libft/

$(MINIGNL):
	make -C minignl/

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(NAME_debug)

re: fclean all

.PHONY: all clean fclean re 