# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/04/24 15:56:32 by skushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= wolf3d

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

SRC			= wolf.c parse.c host.c utility.c handler.c

HDR			= wolf.h

LIB			= libft/libft.a

OBJ			= $(SRC:.c=.o)

INCLUDES	= -F./framework
INCLUDES	+= $(addprefix -I, ./libft/printf ./framework/SDL2.framework/Headers	\
							./framework/SDL2_ttf.framework/Headers					\
							./framework/SDL2_image.framework/Headers)

FRAMEWORKS	=	-rpath ./framework -framework OpenGl -framework AppKit -framework opencl	\
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image


all: lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	$(CC)  $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INCLUDES) $(FRAMEWORKS)

$(OBJ): %.o : %.c $(HDR)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES)

lib:
	make -C libft;
clean:
	@make -C libft clean;
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean;
	@rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re
