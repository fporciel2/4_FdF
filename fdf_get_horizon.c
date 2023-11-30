/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_horizon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:20:30 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/30 19:39:15 by fporciel         ###   ########.fr       */
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

int	fdf_get_horizon_x0(t_fdf *fdf, int x, int y)
{
	int	xiso;
	int	orthx;
	int	orthy;
	int	zfact;

	if (x == 0)
		return (0);
	orthx = fdf_get_orth_x(fdf, (x - 1));
	orthy = fdf_get_orth_y(fdf, y);
	zfact = (fdf->map)[y][x - 1];
	xiso = (int)((orthx - orthy) * cos(0.5));
	xiso += MIDX - fdf->isocx;
	if (zfact > 0)
		fdf->color = RED;
	else if (zfact < 0)
		fdf->color = BLUE;
	else
		fdf->color = WHITE;
	return (xiso);
}

int	fdf_get_horizon_y0(t_fdf *fdf, int x, int y)
{
	int	yiso;
	int	orthx;
	int	orthy;
	int	zfact;

	if (x == 0)
		return (0);
	orthx = fdf_get_orth_x(fdf, (x - 1));
	orthy = fdf_get_orth_y(fdf, y);
	zfact = (fdf->map)[y][x - 1];
	yiso = (int)((orthx + orthy) * sin(0.5) - zfact);
	yiso += MIDY - fdf->isocy;
	if (zfact > 0)
		fdf->color = RED;
	else if (zfact < 0)
		fdf->color = BLUE;
	else
		fdf->color = WHITE;
	return (yiso);
}

int	fdf_get_horizon_x1(t_fdf *fdf, int x, int y)
{
	int	xiso;
	int	orthx;
	int	orthy;
	int	zfact;

	if (x == 0)
		return (0);
	orthx = fdf_get_orth_x(fdf, x);
	orthy = fdf_get_orth_y(fdf, y);
	zfact = (fdf->map)[y][x];
	xiso = (int)((orthx - orthy) * cos(0.5));
	xiso += MIDX - fdf->isocx;
	if (zfact > 0)
		fdf->color = RED;
	else if (zfact < 0)
		fdf->color = BLUE;
	else
		fdf->color = WHITE;
	return (xiso);
}

int	fdf_get_horizon_y1(t_fdf *fdf, int x, int y)
{
	int	yiso;
	int	orthx;
	int	orthy;
	int	zfact;

	if (x == 0)
		return (0);
	orthx = fdf_get_orth_x(fdf, x);
	orthy = fdf_get_orth_y(fdf, y);
	zfact = (fdf->map)[y][x];
	yiso = (int)((orthx + orthy) * sin(0.5) - zfact);
	yiso += MIDY - fdf->isocy;
	if (zfact > 0)
		fdf->color = RED;
	else if (zfact < 0)
		fdf->color = BLUE;
	else
		fdf->color = WHITE;
	return (yiso);
}
