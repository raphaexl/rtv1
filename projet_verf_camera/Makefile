# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/04/25 15:19:27 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -L$(LIBDIR)/ -lft -lm

UNAME_S := $(shell uname -s)

ifeq	($(UNAME_S),Linux)
	LDFLAGS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
	#LDFLAGS = $(CFLAGS) $(LIBDIR)/libft/libft.a -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
endif

ifeq	($(UNAME_S),Darwin)
	SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
	SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
	SDL2_ttf = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
	LDFLAGS += -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
	CFLAGS += -F ./frameworks
endif

SRC=$(SRCDIR)/main.c\
	$(SRCDIR)/input.c\
	$(SRCDIR)/process.c\
	$(SRCDIR)/verbose.c\
	$(SRCDIR)/utils.c\
	$(SRCDIR)/draw.c\
	$(SRCDIR)/load.c\
	$(SRCDIR)/env.c\
	$(SRCDIR)/read.c\
	$(SRCDIR)/parse.c\
	$(SRCDIR)/object.c\
	$(SRCDIR)/light.c\
	$(SRCDIR)/scene.c\
	$(SRCDIR)/sphere.c\
	$(SRCDIR)/cone.c\
	$(SRCDIR)/cylindre.c\
	$(SRCDIR)/plane.c\
	$(SRCDIR)/camera.c\
	$(SRCDIR)/vector1.c\
	$(SRCDIR)/vector2.c\
	$(SRCDIR)/rotation.c\
	$(SRCDIR)/color.c\
	$(SRCDIR)/raytrace.c\
	$(SRCDIR)/pathtrace.c\
	$(SRCDIR)/trace.c\
	$(SRCDIR)/reflections.c\
	$(SRCDIR)/compute.c\
	$(SRCDIR)/normals.c\
	$(SRCDIR)/sdl.c

OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/process.o\
	$(LIBDIR)/verbose.o\
	$(LIBDIR)/utils.o\
	$(LIBDIR)/draw.o\
	$(LIBDIR)/load.o\
	$(LIBDIR)/env.o\
	$(LIBDIR)/read.o\
	$(LIBDIR)/parse.o\
	$(LIBDIR)/object.o\
	$(LIBDIR)/light.o\
	$(LIBDIR)/scene.o\
	$(LIBDIR)/sphere.o\
	$(LIBDIR)/cone.o\
	$(LIBDIR)/cylindre.o\
	$(LIBDIR)/plane.o\
	$(LIBDIR)/camera.o\
	$(LIBDIR)/raytrace.o\
	$(LIBDIR)/pathtrace.o\
	$(LIBDIR)/trace.o\
	$(LIBDIR)/compute.o\
	$(LIBDIR)/normals.o\
	$(LIBDIR)/vector1.o\
	$(LIBDIR)/vector2.o\
	$(LIBDIR)/reflections.o\
	$(LIBDIR)/rotation.o\
	$(LIBDIR)/color.o\
	$(LIBDIR)/sdl.o

NAME=rtv1

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)/libft/ fclean && make -C $(LIBDIR)/libft
	@cp $(LIBDIR)/libft/libft.a $(LIBDIR)/
	$(CC) $(LDFLAGS) -o $@ $^
ifeq ($(UNAME_S),Darwin)
		@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
		@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)
		@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
endif

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o
	make -C $(LIBDIR)/libft clean

fclean:clean
	rm -rf $(NAME)
	make -C $(LIBDIR)/libft fclean

re : fclean all
