# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 14:17:47 by armajchr          #+#    #+#              #
#    Updated: 2020/06/18 15:15:39 by armajchr         ###   ########.fr        #
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
CC		= /usr/bin/gcc - g -fsanitize=address
RM		= /bin/rm
FLAG	= -Wall -Wextra -Werror

NAME	= lem-in
LIB1	= Libft/libft.a
LIB2	= ft_printf/libftprintf.a

HEADER	= incs/lem_in.h
INCLUDE = incs/
SRC		= srcs/ft_create_elem.c	\
		srcs/init_items.c		\
		srcs/utils.c			\
		srcs/utils2.c			\
		srcs/utils3.c			\
		srcs/utils4.c			\
		srcs/parser.c			\
		srcs/parsing.c			\
		srcs/lem_in.c			\
		srcs/get_map_info.c		\
		srcs/bfs.c				\
		srcs/bfs2.c				\
		srcs/way2.c				\
		srcs/solve.c			\
		srcs/solve_utils.c		\
		#srcs/visu.c				\
		#srcs/visu_launch.c		\
		#srcs/visu_render.c		\
		#srcs/visu_move.c		\
		#srcs/visu_load.c

OBJ_PATH = ./obj
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

DEP_NAME = $(SRC_NAME:.c=.d)

.PHONY: all clean fclean re

all: mkdir $(NAME)

mkdir: 
	@mkdir -p $(OBJ_PATH)
	
$(NAME): $(LIB1) $(LIB2) $(SRC) $(HEADER) Makefile
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(SRC) $(LIB1) $(LIB2) -I $(INCLUDE)
	@echo "$(YELLOW)./$(NAME)     $(GREEN)ready   ✅ $(RESET)"
	@install_name_tool -change @rpath/$(SDL2) $(SDL2_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_IMG) $(SDL2_IMG_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_TTF) $(SDL2_TTF_PATH) $(NAME)
	@install_name_tool -change @rpath/$(SDL2_MXR) $(SDL2_MXR_PATH) $(NAME)

-include $(DEP)

$(OBJ_PATH)/%.o : ./srcs/%.c Makefile $(HEADER)
	@gcc $(FLAGS) -I Libft -I ft_printf -I ./incs -MMD -MP -c $< -o $@ -F $(FW_PATH)


$(LIB1): $(LIB2)
	@make -C Libft

$(LIB2):
	@make -C ft_printf

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
