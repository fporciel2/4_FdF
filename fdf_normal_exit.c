/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_normal_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:04:31 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/30 09:59:33 by fporciel         ###   ########.fr       */
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

static char	*fdf_free_string(char *str)
{
	free(str);
	return (NULL);
}

char	**fdf_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		split[i] = fdf_free_string(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	fdf_clean_all(t_fdf *fdf)
{
	if (fdf->line != NULL)
		fdf->line = fdf_free_string(fdf->line);
	if (fdf->spline != NULL)
		fdf->spline = fdf_free_split(fdf->spline);
	if (fdf->img != NULL)
		mlx_destroy_image(fdf->dsp, fdf->img);
	if (fdf->win != NULL)
		mlx_destroy_window(fdf->dsp, fdf->win);
	if (fdf->dsp != NULL)
		mlx_destroy_display(fdf->dsp);
	return (0);
}

int	fdf_memory_cleaner(t_fdf *fdf)
{
	if (fdf && (fdf->fd != 0))
	{
		fdf->fd = close(fdf->fd);
		if (fdf->fd < 0)
		{
			fdf->fd = 0;
			return (fdf_generic_error(fdf));
		}
	}
	return (fdf_clean_all(fdf));
}

int	fdf_normal_exit(t_fdf *fdf)
{
	int	stat;

	stat = fdf_free_map(fdf);
	stat = fdf_memory_cleaner(fdf);
	return (exit(EXIT_SUCCESS), stat);
}
