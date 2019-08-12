# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nmartins <nmartins@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/08/13 00:43:08 by nmartins       #+#    #+#                 #
#    Updated: 2019/08/13 01:00:20 by nmartins      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include colors.mk

NAME=libftimg.a
CC=clang
AR=ar
RM=rm
FLAGS=-Werror -Wall -Wextra

OBJ_DIR=	.obj
OBJ_NAMES=	\
			bitmap \
			bitmap_parse \

OBJECTS=	$(patsubst %, $(OBJ_DIR)/%.o, $(OBJ_NAMES))
SOURCES=	$(patsubst %, %.c, $(OBJ_NAMES))

INCLUDES=	$(wildcard *.h)

$(OBJ_DIR)/%.o: %.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@echo "$(CGREEN)[+]$(CDEF) $@"
	@$(CC) -c -o $@ $< $(FLAGS)

$(NAME): $(OBJECTS)
	@echo "$(CGREEN)[+]$(CDEF) $@"
	@$(AR) rcs $(NAME) $(OBJECTS)

clean:
	@echo "$(CRED)[-]$(CDEF) $(OBJ_DIR)"
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@echo "$(CRED)[-]$(CDEF) $(NAME)"
	@$(RM) -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)