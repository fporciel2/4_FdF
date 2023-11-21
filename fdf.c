/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:18:37 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/21 14:50:47 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * FdF is a general-purpose Computer-Aided Design (CAD) program meant to analyze
 * and render a properly formatted map of a landscape.
 *
 * Copyright (C) 2023  Federico Porciello
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "fdf.h"

static int	fdf_check_filename(char *name)
{
	int		namelen;
	int		fd;

	namelen = ft_strlen(name);
	if ((name[namelen - 1] != 102) || (name[namelen - 2] != 100)
		|| (name[namelen - 3] != 102) || (name[namelen - 4] != 46))
		return (0);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		if (close(fd) < 0)
			return (fdf_nonexistent_file_error());
		return (0);
	}
	if (close(fd) < 0)
		return (fdf_generic_error(NULL));
	return (1);
}

int	main(int argc, char **argv)
{
	static t_fdf	fdf;
	int				i;
	int				j;

	if (argc != 2)
		return (fdf_invalid_argument_error());
	if (!fdf_check_filename(argv[1]))
		return (fdf_nonexistent_file_error());
	fdf.width = 0;
	fdf.height = fdf_get_height_and_width(&fdf, argv[1]) - 1;
	fdf.map = fdf_prepare_map(&fdf, argv[1]);
	fdf.fd = 0;
	//fdf_normal_exit(&fdf);
	ft_printf("Height: %d\n", fdf.height);
	ft_printf("Width: %d\n", fdf.width);
	ft_printf("\n\n");
	i = 0;
	while (((fdf.map)[i]) != NULL)
	{
		j = 0;
		while (j < fdf.width)
		{
			ft_printf("%d ", ((fdf.map)[i][j]));
			j++;
		}
		ft_printf("\n");
		i++;
	}
	fdf_normal_exit(&fdf);
	return (0);
}
