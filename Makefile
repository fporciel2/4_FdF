# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 09:47:25 by fporciel          #+#    #+#              #
#    Updated: 2023/05/21 12:07:41 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# 
# This software is made available to anyone who wants to retrace the 
# author's learning path through the projects of school 42.
# Copyright (C) 2023  fporciel
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
# You can contact the author at: 
#- fporciel@student.42roma.it
#

.PHONY: all clean fclean re all-subdirs configure
.DEFAULT_GOAL := $(NAME)
NAME := fdf
LIB := binfdf.a
LIBS := $(wildcard */*.a)
SUBDIRS := $(filter-out mlx_linux, $(wildcard */*.a))
SRCS := $(wildcard fdf_*.c) $(wildcard **/fdf_*.c) $(wildcard **/mlx_*.c)
HEADERS := $(wildcard *.h) $(wildcard **/*.h)
OBJS := $(patsubst %.c, %.o, $(notdir $(SRCS)))
CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3 -c
LD_FLAGS := -L./mlx_linux -lmlx -lXext -lX11 -lm

$(NAME): $(LIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LD_FLAGS)

$(LIB): $(OBJS) $(HEADERS) $(LIBS)
	ar rcs $@ $^

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $^

$(LIBS): all-subdirs configure

configure:
	cd mlx_linux && ./configure
	cd ..

all-subdirs: $(SUBDIRS)
	for dir in $^; do $(MAKE) -C $$dir done
