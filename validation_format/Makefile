# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/10/02 12:06:24 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	fractol
LFT		:=	libft.a

ifeq ($(OS),Windows_NT)
	PLATFORM := WINDOWS
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM := LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM := MACOS
	endif
endif

#PLATFORM:=	LINUX
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra -O3

HDRDIR	:=	./
LFTDIR	:=	./libft/
TSTDIR	:=	./tests/
SRCDIR	:=	./src/


ifeq ($(PLATFORM),LINUX)
DBFLAGS :=	-fsanitize=address
LIBASAN :=	-lasan
LOC_LX	:=	/usr/lib/x86_64-linux-gnu/
LIB_SUFF:=	_Linux
LOC_LMLX:=	../mlx_reqs/
LIBS	:=	$(LIBASAN) -L$(LOC_LMLX) -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -lm -L$(LOC_LX) -lX11 -lXext
endif

ifeq ($(PLATFORM),WINDOWS)
DBFLAGS :=	
LIBASAN :=	
LOC_LX	:=	/usr/include/X11/
LIB_SUFF:=	_x86_64
LOC_LMLX:=	
LIBS	:=	-L$(LOC_LMLX) -I$(LOC_LX) -lmlx -L$(LFTDIR) -lft -lX11.dll -lXext.dll
endif

ifeq ($(PLATFORM),MACOS)
DBFLAGS :=	
LIBASAN :=
LOC_LX	:=	/usr/X11/lib
LIB_SUFF:=
LOC_LMLX:=		
LIBS	:= -lmlx -framework OpenGL -framework AppKit -L$(LFTDIR) -lft
endif


HDRS	:=	$(NAME).h
SRCS	:=	fractals.c			\
			image_utils.c		\
			event_key.c			\
			event_mouse.c		\
			polynom_rdr.c		\
			render.c			\
			m_s_rect.c			\
			dwell_utils.c		\
			figures.c			\
			bresenham.c

OBJS	:=	$(SRCS:.c=.o)

MAIN	:=	main_$(NAME).c
OBJ_MAIN:=	$(MAIN:.c=.o)

TST_DIR		:=	unit_tests
TST_MAIN	:=	$(TST_DIR)/unit_tests.c
TST_EXEC	:=	test.out

RESET	:=	"\033[0m"
RED		:=	"\033[0;31m"
GREEN	:=	"\033[0;32m"

$(NAME): $(LFTDIR)$(LFT) $(OBJS) $(OBJ_MAIN) $(HDRS)
	@echo "Compiling software: "$@" -> \c"$(RED)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(OBJ_MAIN) $(LIBS) -o $@
	@echo $(GREEN)"OK!"$(RESET)

%.o: $(SRCDIR)%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR)

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
	@rm -f $@
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	@rm -f $(OBJS) $(OBJ_MAIN)

fclean:clean
	$(MAKE) -C $(LFTDIR) fclean
	@rm -f $(NAME)

re:fclean all

test:$(LFTDIR)$(LFT) $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(TST_MAIN) $(LIBS) -o $(TST_EXEC)
	./$(TST_EXEC)
	@rm -f $(TST_MAIN:.c=.o) $(TST_EXEC)

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
