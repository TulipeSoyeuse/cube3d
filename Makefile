# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romain <romain@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 14:30:15 by romain            #+#    #+#              #
#    Updated: 2024/02/10 14:50:46 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES 		= $(wildcard $(SRC_DIR)/*.c)
SRC_DIR 		= srcs
OBJ_DIR 		= objs
SRC 			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ 			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJ_debug		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=_debug.o))
HEADER_DIR 		= includes
LIBFT			= $(LIBFT_DIR)/libft.a
CC				= cc
CFLAGS 			= -Wextra -Wall -Werror
Xext 			= /opt/homebrew/Cellar/libxext/1.3.5/lib
X11 			= /opt/homebrew/Cellar/libx11/1.8.7/lib
NAME			= cub3d
NAME_debug		= cub3d_debug

all: $(NAME)

db: $(NAME_debug)

$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g3 -I$(HEADER_DIR) -L$(Xext) -lXext -L$(X11) -lX11 -c -o $@ $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -L$(Xext) -lXext -L$(X11) -lX11 -c -o $@ $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_debug): $(OBJ_debug)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 