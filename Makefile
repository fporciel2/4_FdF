# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 09:12:59 by fporciel          #+#    #+#              #
#    Updated: 2023/11/21 09:17:49 by fporciel         ###   ########.fr        #
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
	printf norm memcheck bmemcheck helgrind bhelgrind
.DEFAULT_GOAL: all
NAME := fdf
BNAME := bfdf
DIR := $(shell pwd)
DMLX := $(DIR)/minilibx-linux
DFT := $(DIR)/1_libft
DPRINTF := $(DIR)/2_ft_printf
DINCLUDE := $(DIR) $(DMLX) $(FT) $(DPRINTF)
FDFH := $(DIR)/fdf.h
BFDFH := $(DIR)/fdf_bonus.h
MLXH := $(DMLX)/mlx.h $(DMLX)/mlx_int.h
FTH := $(DFT)/libft.h
PRINTFH := $(DPRINTF)/ft_printf.h
HEADERS := $(FDFH) $(MLXH) $(FTH) $(PRINTFH)
BHEADERS := $(BFDFH) $(MLXH) $(FTH) $(PRINTFH)
LFDF := $(DIR)/libfdf.a
LBFDF := $(DIR)/libfdfbonus.a
LMLX := $(DMLX)/libmlx.a $(DMLX)/libmlx_Linux.a
LFT := $(DFT)/libft.a
LPRINTF := $(DPRINTF)/libftprintf.a
LIBS := $(LFT) $(LPRINTF) $(LMLX)
BLIBS := $(LFT) $(LPRINTF) $(MLX)
SRCS := $(filter-out %bonus.c, $(wildcard fdf*.c))
BSRCS := $(wildcard fdf*bonus.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
BOBJS := $(patsubst %.c, %.o, $(BSRCS))
CC := gcc
CFLAGS := gcc -std=c17 -pedantic -Wall -Wextra -Werror -O3 -march=native -g \
		  $(addprefix -I, $(DINCLUDE))
LDLIBS := $(addprefix -L, $(DINCLUDE))
LDFLAGS := -lmlx -lft -lftprintf -lXext -lX11 -lm

all: ft printf mlx $(NAME)

$(NAME): $(LFDF)
	$(CC) $(CFLAGS) $(LFDF) $(LDLIBS) $(LDFLAGS) -o $@

bonus: ft printf mlx $(BNAME)

$(BNAME): $(LBFDF)
	$(CC) $(CFLAGS) $(LBFDF) $(LDLIBS) $(LDFLAGS) -o $@

$(LFDF): $(OBJS)
	ar rcs $@ $(OBJS) $(HEADERS)

$(LBFDF): $(BOBJS)
	ar rcs $@ $(BOBJS) $(BHEADERS)

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS)

$(BOBJS): $(BSRCS) $(BHEADERS)
	$(CC) $(CFLAGS) $(BSRCS)

mlx: $(LMLX)

$(LMLX): dmlx
	if [ ! -e $@ ]; \
		then cd $(DMLX) && ./configure && cd ..; fi

printf: $(LPRINTF)

$(LPRINTF): dprintf ft
	if [ ! -e $@ ]; \
		then cd $(DPRINTF) && make && cd ..; fi

ft: $(LFT)

$(LFT): dft
	if [ ! -e $@ ]; \
		then cd $(DFT) && make bonus && cd ..; fi

dprintf: $(DPRINTF)

$(DPRINTF):
	if [ ! -e $@ ]; \
		then git clone git@github.com:fporciel2/2_ft_printf.git; fi

dft: $(DFT)

$(DFT):
	if [ ! -e $@ ]; \
		then git clone git@github.com:fporciel2/1_libft.git; fi

dmlx: $(DMLX)

$(DMLX):
	if [ ! -e $@ ]; \
		then git clone git@github.com:42Paris/minilibx-linux.git; fi

clean:
	rm -f $(OBJS)
	rm -f $(BOBJS)
	if [ -e $(DFT) ]; \
		then cd $(DFT) && make clean && cd ..; fi
	if [ -e $(DPRINTF) ]; \
		then cd $(DPRINTF) && make clean && cd ..; fi

fclean: clean
	rm -f $(NAME) $(BNAME) $(LIBS) $(BLIBS)

re: clean fclean all

rebonus: clean fclean bonus

dfclean: clean fclean
	rm -rfd $(DFT)
	rm -rfd $(DPRINTF)
	rm -rfd $(DMLX)

autogit: dfclean
	git status
	git add *
	git status
	echo "\nPlease, enter your commit message:"
	read commit_message; git commit -m "$$commit_message"
	git status
	git push

memcheck:
	echo "\nPlease, enter the name of the map:"
	read map_name; \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --show-error-list=yes -s -v ./fdf $$map_name

bmemcheck:
	echo "\nPlease, enter the name of the map:"
	read map_name; \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --show-error-list=yes -s -v ./bfdf $$map_name

helgrind:
	echo "\nPlease, enter the name of the map:"
	read map_name; \
		valgrind --tool=helgrind --history-level=full ./fdf $$map_name

bhelgrind:
	echo "\nPlease, enter the name of the map:"
	read map_name; \
		valgrind --tool=helgrind --history-level=full ./bfdf $$map_name

