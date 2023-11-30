/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:01:49 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/30 11:04:21 by fporciel         ###   ########.fr       */
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

int	fdf_get_vert_x0(t_fdf *fdf, int x, int y)
{
	int	xiso;

	if (y == 0)
		return (0);
	xiso = (int)(((sqrt(2) / 2) * (fdf_get_orth_x(fdf, x) - MIDX))
			- ((sqrt(2) / 2) * (fdf_get_orth_y(fdf, (y - 1)) - MIDY)) + MIDX);
	return (xiso);
}

int	fdf_get_vert_y0(t_fdf *fdf, int x, int y)
{
	int	yiso;

	if (y == 0)
		return (0);
	yiso = (int)(((sqrt(6) / 6) * (fdf_get_orth_x(fdf, x) - MIDX))
			- ((sqrt(6) / 6) * (fdf_get_orth_y(fdf, (y - 1)) - MIDY))
			- (((sqrt(6) / 3) * fdf->map[y - 1][x]) + MIDY));
	return (yiso);
}

int	fdf_get_vert_x1(t_fdf *fdf, int x, int y)
{
	int	xiso;

	if (y == 0)
		return (0);
	xiso = (int)(((sqrt(2) / 2) * (fdf_get_orth_x(fdf, x) - MIDX))
			- ((sqrt(2) / 2) * (fdf_get_orth_y(fdf, y) - MIDY)) + MIDX);
	return (xiso);
}

int	fdf_get_vert_y1(t_fdf *fdf, int x, int y)
{
	int	yiso;

	if (y == 0)
		return (0);
	yiso = (int)(((sqrt(6) / 6) * (fdf_get_orth_x(fdf, x) - MIDX))
			- ((sqrt(6) / 6) * (fdf_get_orth_y(fdf, y) - MIDY))
			- (((sqrt(6) / 3) * fdf->map[y][x]) + MIDY));
	return (yiso);
}
