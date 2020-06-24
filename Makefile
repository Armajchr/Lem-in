# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 14:17:47 by armajchr          #+#    #+#              #
#    Updated: 2020/06/24 13:47:32 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

#SDL
FW_PATH = ./Visu/frameworks
SDL2 = SDL2.framework/Versions/A/SDL2
SDL2_IMG = SDL2_image.framework/Versions/A/SDL2_image
SDL2_TTF = SDL2_ttf.framework/Versions/A/SDL2_ttf
SDL2_MXR = SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_PATH = $(FW_PATH)/$(SDL2)
SDL2_IMG_PATH = $(FW_PATH)/$(SDL2_IMG)
SDL2_TTF_PATH = $(FW_PATH)/$(SDL2_TTF)
SDL2_MXR_PATH = $(FW_PATH)/$(SDL2_MXR)

#Binaries
# CC		= /usr/bin/gcc -g -fsanitize=address
CC		= /usr/bin/gcc
RM		= /bin/rm
FLAGS	= -Wall -Wextra -Werror

NAME	= lem-in
LIB1	= Libft/libft.a
LIB2	= ft_printf/libftprintf.a

HEADER	= incs/lem_in.h
INCLUDE = incs/

SRC		= ft_create_elem.c	\
		init_items.c		\
		utils.c			\
		utils2.c			\
		utils3.c			\
		utils4.c			\
		utils5.c			\
		parser.c			\
		parsing.c			\
		lem_in.c			\
		get_map_info.c		\
		bfs.c				\
		bfs2.c				\
		way2.c				\
		solve.c			\
		solve_utils.c		\
		#srcs/visu.c				\
		srcs/visu_launch.c		\
		srcs/visu_render.c		\
		srcs/visu_move.c		\
		srcs/visu_load.c

OBJ_PATH = obj
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

DEP_NAME = $(SRC_NAME:.c=.d)

.PHONY: all clean fclean re

all: mkdir $(NAME)

mkdir: 
	@mkdir -p $(OBJ_PATH)
	
$(NAME): $(LIB1) $(LIB2) $(OBJ) $(HEADER) Makefile
	clang -g $(FLAGS) -o $(NAME) $(OBJ) $(LIB1) $(LIB2) -I $(INCLUDE)
	@echo "$(YELLOW)./$(NAME)     $(GREEN)ready   ✅ $(RESET)"
	@install_name_tool -change @rpath/$(SDL2) $(SDL2_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_IMG) $(SDL2_IMG_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_TTF) $(SDL2_TTF_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_MXR) $(SDL2_MXR_PATH) $(NAME)

-include $(DEP)

$(OBJ_PATH)/%.o : ./srcs/%.c $(INCLUDE) $(HEADER)
	gcc $(FLAGS) -I Libft -I ft_printf -I ./incs -MMD -MP -c $< -o $@ -F $(FW_PATH)

$(LIB1): $(LIB2) force
	make -C Libft

$(LIB2): force
	make -C ft_printf

force:
	@true

clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW).o        $(RED)deleted 💯 $(RESET)"
	@rm -f $(DEP)
	@echo "$(YELLOW).d        $(RED)deleted 💯 $(RESET)"
	@rm -rf $(OBJ_PATH)
	@make -C Libft clean
	@make -C ft_printf clean

fclean: clean
	@make -C Libft fclean
	@make -C ft_printf fclean
	@$(RM) -f $(NAME)
	@echo "$(YELLOW)./$(NAME)     $(RED)deleted 💯 $(RESET)"

re: fclean all
