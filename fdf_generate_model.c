/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:01:25 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/02 14:30:51 by fporciel         ###   ########.fr       */
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

static int	fdf_get_vert_color(t_fdf *fdf, int x, int y)
{
	int	z0;
	int	z1;

	if ((y == 0) || (((fdf->map)[y][x] >= 0) && ((fdf->map)[y - 1][x] >= 0)
			&& ((fdf->map)[y][x] < 10) && ((fdf->map)[y - 1][x] < 10)))
		return (WHITE);
	z0 = (fdf->map)[y - 1][x];
	z1 = (fdf->map)[y][x];
	if ((z0 < 0) && (z1 == 0))
		return (CYAN);
	else if ((z0 < 0) && (z1 < 0) && (z1 > z0))
		return (AZURE);
	else if ((z0 < 0) && (z1 > 0))
		return (SUPERAZ);
	else if (((z0 < 0) && (z1 < z0)) || ((z0 == 0) && (z1 < 0)))
		return (BLUE);
	else if (((z0 == 0) && (z1 > 0)) || ((z0 > 0) && (z1 > z0)))
		return (RED);
	else
		return (BRICK_RED);
}

static int	fdf_get_horizon_color(t_fdf *fdf, int x, int y)
{
	int	z0;
	int	z1;

	if ((x == 0) || (((fdf->map)[y][x] == 0) && ((fdf->map)[y][x - 1] == 0)
			&& ((fdf->map)[y][x] < 10) && ((fdf->map)[y][x - 1] < 10)))
		return (WHITE);
	z0 = (fdf->map)[y][x - 1];
	z1 = (fdf->map)[y][x];
	if ((z0 < 0) && (z1 == 0))
		return (CYAN);
	else if ((z0 < 0) && (z1 < 0) && (z1 > z0))
		return (AZURE);
	else if ((z0 < 0) && (z1 > 0))
		return (SUPERAZ);
	else if (((z0 < 0) && (z1 < z0)) || ((z0 == 0) && (z1 < 0)))
		return (BLUE);
	else if (((z0 == 0) && (z1 > 0)) || ((z0 > 0) && (z1 > z0)))
		return (RED);
	else
		return (BRICK_RED);
}

static int	fdf_vertical_line(t_fdf *fdf, int x, int y)
{
	fdf->x0 = fdf_get_vert_x0(fdf, x, y);
	fdf->y0 = fdf_get_vert_y0(fdf, x, y);
	fdf->x1 = fdf_get_vert_x1(fdf, x, y);
	fdf->y1 = fdf_get_vert_y1(fdf, x, y);
	fdf->color = fdf_get_vert_color(fdf, x, y);
	if (y != 0)
		fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
	fdf->imap = fdf_clean_line_parameters(fdf);
	return (fdf->imap);
}

int	fdf_generate_model(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->x0 = fdf_get_horizon_x0(fdf, x, y);
			fdf->y0 = fdf_get_horizon_y0(fdf, x, y);
			fdf->x1 = fdf_get_horizon_x1(fdf, x, y);
			fdf->y1 = fdf_get_horizon_y1(fdf, x, y);
			fdf->color = fdf_get_horizon_color(fdf, x, y);
			if (x != 0)
				fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
			fdf->imap = fdf_clean_line_parameters(fdf);
			fdf->imap = fdf_vertical_line(fdf, x, y);
			x++;
		}
		y++;
	}
	return (fdf->imap);
}
