# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/05/04 15:55:14 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -I$(HEADDIR) -L$(LIBDIR)/ -lSDL2 -lSDL2_image -lSDL2_ttf -framework OpenCL

SRC=$(SRCDIR)/main.c\
	$(SRCDIR)/sdl.c\
	$(SRCDIR)/input.c\
	$(SRCDIR)/opencl1.c\
	$(SRCDIR)/opencl2.c

OBJ=$(LIBDIR)/main.o\
		$(LIBDIR)/sdl.o\
		$(LIBDIR)/input.o\
		$(LIBDIR)/opencl1.o\
		$(LIBDIR)/opencl2.o

NAME=opencl

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o

fclean:clean
	rm -rf $(NAME)

re : fclean all
