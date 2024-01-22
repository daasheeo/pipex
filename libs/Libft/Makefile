# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 18:25:29 by jesmunoz          #+#    #+#              #
#    Updated: 2024/01/17 10:27:23 by jesmunoz         ###   ########.fr        #
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

NAME 		= libft.a
OBJ_DIR		= obj
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g -MMD
RM			= 	rm -rf

SRC_FILES   =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
					ft_toupper.c ft_tolower.c ft_strlen.c ft_strchr.c ft_strrchr.c \
					ft_strncmp.c ft_strlcat.c ft_strlcpy.c ft_strdup.c ft_bzero.c \
					ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
					ft_atoi.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c ft_strtrim.c ft_substr.c \
					ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c
BNS_SRCS    =   ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
                    ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
BNS_OBJS	=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(BNS_SRCS))
DEP			= 	$(addsuffix .d, $(basename $(SRC_FILES)))
BNS_DEP		= 	$(addsuffix .d, $(basename $(BNS_SRCS)))


all: 
	@$(MAKE) $(NAME)

bonus: $(NAME) $(BNS_OBJS)
	@ar rcs $(NAME) $(BNS_OBJS)
	@echo "\n${BLUE} ◎ $(GREEN)$(NAME) with bonus compiled successfully ${BLUE}◎$(DEF_COLOR)\n"

$(OBJ_DIR)/%.o: %.c libft.h Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\n${BLUE} ◎ $(GREEN)$(NAME) compiled successfully ${BLUE}◎$(DEF_COLOR)\n"

clean:
	@${RM} ${OBJS} ${DEP} ${BONUS_DEP} 
	@$(RM) ./$(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re