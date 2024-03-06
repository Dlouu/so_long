# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 10:41:57 by mbaumgar          #+#    #+#              #
#    Updated: 2024/03/04 18:44:47 by mbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

ARFLAGS 	= -crs
RM			= rm -rf
LFT			= ./lib/libft.a
LMLX		= ./lib/libmlx42.a
LIBFT		= ./lib/libft
LIBMLX		= ./lib/MLX42
MAKE_LIBFT	= ${MAKE} --no-print-directory -C ${LIBFT}
MAKE_LIBMLX	= @cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4

ifeq ($(shell uname), Linux)
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./includes -I $(LIBMLX)/include
LIBS		= ${LFT} ${LMLX} -ldl -lglfw -pthread -lm
else
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./includes -I/opt/X11/include -Imlx
LIBS		= ./lib/libft.a ./lib/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
endif
DEBUG		= -fsanitize=address -fsanitize=leak -g3

YELLOW		= \033[1;33m# bold / yellow
RED			= \033[1;31m# bold / red
BACKGROUND	= \033[7;33m# background / yellow
BLINK		= \033[5;2;39m# blink / gray
END			= \033[m# remove style

# *****************************************************************************
#  ┌─┐┌─┐┬ ┬┬─┐┌─┐┌─┐┌─┐
#  └─┐│ ││ │├┬┘│  ├┤ └─┐
#  └─┘└─┘└─┘┴└─└─┘└─┘└─┘

SRC_DIR			= ./src/
OUT_DIR			= ./bin/
MAP_ERROR_DIR 	= maps/error/*

SRC				= main.c parsing.c parsing_map.c path.c loading_img.c render.c \
				controls.c win.c utils.c

OBJ				= ${SRC:%.c=${OUT_DIR}%.o}

# *****************************************************************************
#  ┬─┐┬ ┬┬  ┌─┐┌─┐
#  ├┬┘│ ││  ├┤ └─┐
#  ┴└─└─┘┴─┘└─┘└─┘

all: ${LFT} ${LMLX} ${NAME}

${LFT}: 
	@${MAKE_LIBFT}

${LMLX}:
	@${MAKE_LIBMLX} --no-print-directory
	@mv ${LIBMLX}/build/libmlx42.a ./lib/

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJ} ${LIBS} ${INCLUDES}
	@echo " ${YELLOW}so_long${END} is ready !\n\n \
	${CYAN} Have fun ! ${END}    ${BLINK}Yeah!${END} ᕙ ( •̀ ᴗ •́ )ᕗ\n" 

${OUT_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p ${OUT_DIR}
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@${MAKE_LIBFT} clean
	@${RM} ${OUT_DIR}
	@echo "🧹 ${RED}removed:${END} objects"
	@${RM} ${LIBMLX}/build/

fclean: clean
	@${RM} ${NAME}
	@${MAKE_LIBFT} fclean
	@${RM} ${LMLX}
	@echo "🧹 ${RED}removed:${END} archives and so_long\n \
	 ${BACKGROUND} Everything has been DESTROYED!! ${END} ( •̀ ᴖ •́ )\n"

re: fclean all

uwu: re
	@${MAKE} --no-print-directory clean

norminette:
	norminette lib/libft/src/*
	@echo "\n"
	norminette includes/*
	@echo "\n"
	norminette src/*

sanitize: re
	${CC} ${CFLAGS} ${DEBUG} -o ${NAME} ${OBJ} ${LIBS} ${INCLUDES}

reset_scores:
	@rm -rf maps/high_score.txt
	@echo -n "ALL FEWER MOVES HIGH SCORES | " > maps/high_score.txt
	@echo "All high scores have been erased"

test:
	for map in $(MAP_ERROR_DIR) ; do \
		echo "$ \n •·················•·················• \n${YELLOW}\n$$map" ; \
		echo "${END}" ; \
		cat $$map ; \
		echo "\n" ; \
		./so_long $$map || true ; \
	done
	
.PHONY: all clean fclean re uwu norminette sanitize reset_scores test
