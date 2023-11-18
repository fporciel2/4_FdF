# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 09:12:59 by fporciel          #+#    #+#              #
#    Updated: 2023/11/18 14:03:40 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# FdF is a general-purpose Computer-Aided Design (CAD) program meant to analyze
# and render a properly formatted map of a landscape.
#
# Copyright (C) 2023  Federico Porciello
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

.PHONY: all bonus clean fclean dfclean re rebonus dmlx mlx dft ft dprintf \
	printf norm memcheck helgrind
.DEFAULT_GOAL: all
NAME := fdf
BNAME := bfdf
DIR := $(shell pwd)
DMLX := $(DIR)/minilibx-linux
DFT := $(DIR)/1_libft
DPRINTF := $(DIR)/2_ft_printf
DINCLUDE := $(DIR) $(DMLX) $(FT) $(DPRINTF)
FDFH := $(DIR)/$(filter-out %bonus.h, $(wildcard *.h))
BFDFH := $(DIR)/$(wildcard *bonus.h)
MLXH := $(DMLX)/$(wildcard *.h)
FTH := $(DFT)/$(wildcard *.h)
PRINTFH := $(DPRINTF)/$(wildcard *.h)
HEADERS := $(FDFH) $(MLXH) $(FTH) $(PRINTFH)
BHEADERS := $(BFDFH) $(MLXH) $(FTH) $(PRINTFH)
LFDF := $(DIR)/libfdf.a
LBFDF := $(DIR)/libfdfbonus.a
LMLX := $(DMLX)/libmlx.a $(DMLX)/libmlx_Linux.a
LFT := $(DFT)/libft.a
LPRINTF := $(DPRINTF)/libftprintf.a
LIBS := $(LFT) $(LPRINTF) $(LMLX) $(LFDF)
BLIBS := $(LFT) $(LPRINTF) $(MLX) $(LBFDF)
SRCS := $(filter-out %bonus.c, $(wildcard fdf*.c))
BSRCS := $(wildcard fdf*bonus.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
BOBJS := $(patsubst %.c, %.o, $(BSRCS))
CC := gcc
CFLAGS := gcc -std=c17 -pedantic -Wall -Wextra -Werror -O3 -march=native -g \
		  $(addprefix -I, $(DINCLUDE))
LDLIBS := $(addprefix -L, $(DINCLUDE))
LDFLAGS := -lmlx -lft -lftprintf -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBS)
	$(CC) $(CFLAGS) $(LFDF) $(LDLIBS) $(LDFLAGS) -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(BLIBS)
	$(CC) $(CFLAGS) $(LBFDF) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(LIBS): $(LFDF)

$(BLIBS): $(LBFDF)

$(LFDF): $(OBJS)
	ar rcs $(LFDF) $(OBJS) $(HEADERS)

$(LBFDF): $(BOBJS)
	ar rcs $(LBFDF) $(BOBJS) $(BHEADERS)

$(OBJS): ft printf mlx $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS)

$(BOBJS): ft printf mlx $(BSRCS) $(BHEADERS)
	$(CC) $(CFLAGS) $(BSRCS)

mlx: $(LMLX)

$(LMLX): dmlx
	if [ ! -e $(LMLX) ]; \
		then cd $(DMLX) && ./configure && cd ..; fi

printf: $(LPRINTF)

$(LPRINTF): dprintf ft
	if [ ! -e $(LPRINTF) ]; \
		then cd $(DPRINTF) && make && cd ..; fi

ft: $(LFT)

$(LFT): dft
	if [ ! -e $(LFT) ]; \
		then cd $(DFT) && make bonus && cd ..; fi

dprintf: $(DPRINTF)

$(DPRINTF):
	if [ ! -e $(DPRINTF) ]; \
		then git clone git@github.com:fporciel2/2_ft_printf.git; fi

dft: $(DFT)

$(DFT):
	if [ ! -e $(DFT) ]; \
		then git clone git@github.com:fporciel2/1_libft.git; fi

dmlx: $(DMLX)

$(DMLX):
	if [ ! -e $(DMLX) ]; \
		then git clone git@github.com:42Paris/minilibx-linux.git; fi
