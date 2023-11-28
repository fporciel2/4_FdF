/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_model.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:37:29 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/28 15:28:50 by fporciel         ###   ########.fr       */
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

/*
 *void	space_and_scale(t_date *inf)
{
	double	may;
	double	might;
	double	ipo;

	ipo = sqrt((pow(inf->colums - 1, 2) + pow(inf->rows - 1, 2)));
	may = inf->width / ipo;
	might = inf->height / ipo;
	inf->scaling = fmin(may, might);
	inf->center_x = (inf->width - (inf->scaling * (inf->colums - 1))) / 2;
	inf->center_y = (inf->height - (inf->scaling * (inf->rows - 1))) / 2;
}
 *
 *
 * */

/*
 *void	int_to_isometric_pixel(t_date *info, t_point **head)
{
	t_point	*current;

	current = *head;
	while (current != NULL)
	{
		current->x_pixel = (info->center_x) + ((current->x_map - current->y_map)
				* cos(PI / 6) * info->scaling);
		current->y_pixel = (info->center_y) - (current->z_map * sin(PI / 6)
				* info->scaling) + ((current->x_map + current->y_map)
				* sin(PI / 6) * info->scaling);
		current = current->next;
	}
}
 *
 */

int	fdf_draw_model(t_fdf *fdf, int x, int y)
{
	(void)x;
	(void)y;
	fdf_put_pixel(fdf, fdf->cur->x, fdf->cur->y, WHITE);
	return (fdf->imap);
}
