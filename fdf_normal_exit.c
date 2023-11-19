/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_normal_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:04:31 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/19 11:25:02 by fporciel         ###   ########.fr       */
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

static int	fdf_clean_all(t_fdf *fdf)
{
	(void)fdf;
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

	stat = fdf_memory_cleaner(fdf);
	return (exit(EXIT_SUCCESS), stat);
}