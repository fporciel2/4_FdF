# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 09:12:59 by fporciel          #+#    #+#              #
#    Updated: 2023/11/18 13:48:20 by fporciel         ###   ########.fr        #
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

$(LIBS): ft printf mlx $(LFDF)

$(BLIBS): ft printf mlx $(LBFDF)

$(LFDF): $(OBJS)
	ar rcs $(LFDF) $(OBJS) $(HEADERS)

$(LBFDF): $(BOBJS)
	ar rcs $(LBFDF) $(BOBJS) $(BHEADERS)

mlx: $(LMLX)

$(LMLX): $(DMLX)
	cd $(DMLX) && ./configure && cd ..

printf: $(LPRINTF)

$(LPRINTF): dprintf ft
	cd $(DPRINTF) && make && cd ..

ft: $(LFT)

$(LFT): dft
	cd $(DFT) && make bonus && cd ..

dprintf: $(DPRINTF)

$(DPRINTF):
	git clone git@github.com:fporciel2/2_ft_printf.git

dft: $(DFT)

$(DFT):
	git clone git@github.com:fporciel2/1_libft.git

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS)

$(BOBJS): $(BSRCS) $(BHEADERS)
	$(CC) $(CFLAGS) $(BSRCS)
