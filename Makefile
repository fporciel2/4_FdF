# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 09:47:25 by fporciel          #+#    #+#              #
#    Updated: 2023/05/21 20:16:34 by fporciel         ###   ########.fr        #
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

.PHONY: all clean fclean re mlx-config-start make-subdirs norm
.DEFAULT_GOAL := $(NAME)
NAME := fdf
LIB := progfdf.a
LIBS := $(wildcard **/*.a)
SRCS := $(wildcard fdf*.c)
HEADERS := $(wildcard *.h)
OBJS := $(patsubst %.c, %.o, $(SRCS))
SUBDIRS := $(filter-out ./mlx_linux/%, $(wildcard ./*/))
LIB_DIRS := $(addprefix ./, $(wildcard */))
LIB_FLAGS := $(addprefix -L, $(LIB_DIRS))
CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3
LD_FLAGS := $(LIB_FLAGS) -lfdf -lmlx -lft -lXext -lX11 -lm

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(addprefix -I, $(LIB_DIRS)) progfdf.a $(LD_FLAGS) -o $@

all: $(NAME)

$(LIB): mlx-config-start make-subdirs $(OBJS)
	ar rcs $@ $(OBJS) $(HEADERS) $(LIBS)

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -c $^

mlx-config-start:
	cd mlx_linux && ./configure

make-subdirs:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

clean:
	rm -f $(OBJS) $(wildcard **/*.o)

fclean: clean
	rm -f $(LIBS) $(LIB) $(NAME)

re: fclean all

norm:
	norminette $(filter-out mlx_linux/%, $(SRCS) $(wildcard **/*.c))

