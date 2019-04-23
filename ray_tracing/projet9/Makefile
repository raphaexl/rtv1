# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/04/23 22:41:52 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -I$(HEADDIR) -L$(LIBDIR)/ -lft -lm -lSDL2 -lSDL2_image -lSDL2_ttf

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
	$(SRCDIR)/trace.c\
	$(SRCDIR)/compute.c\
	$(SRCDIR)/intersections.c\
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
	$(LIBDIR)/trace.o\
	$(LIBDIR)/compute.o\
	$(LIBDIR)/intersections.o\
	$(LIBDIR)/normals.o\
	$(LIBDIR)/vector1.o\
	$(LIBDIR)/vector2.o\
	$(LIBDIR)/rotation.o\
	$(LIBDIR)/color.o\
	$(LIBDIR)/sdl.o

NAME=rtv1

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBDIR)/libft/ fclean && make -C $(LIBDIR)/libft
	cp $(LIBDIR)/libft/libft.a $(LIBDIR)/
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o
	make -C $(LIBDIR)/libft clean

fclean:clean
	rm -rf $(NAME)
	make -C $(LIBDIR)/libft fclean

re : fclean all
