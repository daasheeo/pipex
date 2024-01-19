# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 09:58:28 by jesmunoz          #+#    #+#              #
#    Updated: 2024/01/18 19:47:20 by jesmunoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#------------------------------------COLORS------------------------------------#
#------------------------------------------------------------------------------#
ITALIC 		=	\033[3m
BOLD 		=	\033[1m
DEF_COLOR 	=	\033[0;39m
RED 		=	\033[0;91m
GREEN 		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE 		=	\033[0;94m
MAGENTA 	=	\033[0;95m
CYAN 		=	\033[0;96m
WHITE 		=	\033[0;97m
BROWN 		=	\033[38;2;184;143;29m

#------------------------------------------------------------------------------#
#-----------------------------------PROGRAM------------------------------------#
#------------------------------------------------------------------------------#
NAME 		= 	pipex

#------------------------------------------------------------------------------#
#---------------------------------INSTRUCTIONS---------------------------------#
#------------------------------------------------------------------------------#
CC			= 	gcc -I ${INCLUDE} -Wall -Wextra -Werror -MMD -g
RM			= 	rm -rf

#------------------------------------------------------------------------------#
#------------------------------------INIT--------------------------------------#
#------------------------------------------------------------------------------#
SRC_DIR  			= 	src

OBJ_DIR				= 	obj
INCLUDE 			=   ./includes/
#------------------------------------------------------------------------------#
#-----------------------------------FILES--------------------------------------#
#------------------------------------------------------------------------------#

SRC_FILES   		= 	${SRC_DIR}/pipex.c $(SRC_DIR)/run_pipex.c	\
						$(SRC_DIR)/get_path.c $(SRC_DIR)/get_cmd_path.c	\
						$(SRC_DIR)/manager.c $(SRC_DIR)/cmd_generator.c	\
						$(SRC_DIR)/create_pipes.c $(SRC_DIR)/get_fds.c	\
						$(SRC_DIR)/get_next_line.c $(SRC_DIR)/text_to_file.c	\


OBJ			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP			= 	$(addsuffix .d, $(basename $(SRC_FILES)))

#------------------------------------------------------------------------------#
#---------------------------------DEPENDENCIES---------------------------------#
#------------------------------------------------------------------------------#
# CUnit library for testing
# CUNIT_LNK	=	-L/Users/jesmunoz/.brew/Cellar/cunit/2.1-3/lib -lcunit
# CUNIT_LNK	=	-L/usr/include/CUnit -lcunit
LIBFT_SRC	=	${INCLUDE}/Libft
FT_LNK		= 	-L$(LIBFT_SRC) -lft
#------------------------------------------------------------------------------#
#-----------------------------------RULES--------------------------------------#
#------------------------------------------------------------------------------#

all: 
	@$(MAKE) -C $(LIBFT_SRC)
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	@echo  "${WHITE}+---------------------------------------+${DEF_COLOR}"
	@echo  "${WHITE}|${BLUE} File Name: ${BROWN}$(notdir $<)"
	@echo  "${WHITE}|${CYAN} Path:      ${YELLOW}$(dir $<)"
	@echo  "${WHITE}+---------------------------------------+${DEF_COLOR}"
	@$(CC) -c $< -o $@

-include $(DEP)

$(NAME):	$(OBJ)
	@echo
	@echo "${ITALIC}${BOLD}${MAGENTA}+---------------------------------------------+${DEF_COLOR}"
	@echo "${ITALIC}${BOLD}${MAGENTA}|${BLUE} Compiling ${NAME}...${MAGENTA}                      |${DEF_COLOR}"
	@echo "${ITALIC}${BOLD}${MAGENTA}+---------------------------------------------+${DEF_COLOR}"
	@$(CC) $(OBJ) $(CUNIT_LNK) $(FT_LNK) -o $(NAME) 
	@echo "\n${BLUE} ◎ $(GREEN)$(NAME) compiled successfully ${BLUE}◎$(DEF_COLOR)\n"

clean:
	@${RM} ${OBJ} ${DEP}
	@$(RM) ./$(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_SRC) clean
	@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_SRC) fclean
	@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully${BLUE} ◎$(DEF_COLOR)\n"


re: fclean all

.PHONY: all clean fclean re