/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_height_and_width.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:42:52 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/21 11:08:37 by fporciel         ###   ########.fr       */
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

static void	fdf_get_width(t_fdf *fdf)
{
	int	width;
	int	i;

	width = 0;
	i = 0;
	while (((fdf->line)[i]) != 0)
	{
		if (!ft_isdigit((fdf->line)[i]))
		{
			width++;
			while ((fdf->line)[i] && !ft_isdigit((fdf->line)[i]))
				i++;
		}
		if ((fdf->line)[i] != 0)
			i++;
	}
	if (width > fdf->width)
		fdf->width = width;
}

int	fdf_get_height_and_width(t_fdf *fdf, char *argvi)
{
	fdf->height = 0;
	fdf->stop = 1;
	fdf->fd = open(argvi, O_RDONLY);
	if (fdf->fd < 0)
		return (fdf_generic_error(fdf));
	while (fdf->stop != 0)
	{
		errno = 0;
		fdf->line = get_next_line(fdf->fd);
		if ((fdf->line == NULL) && ((errno == ENOMEM)
				|| (errno == EAGAIN) || (errno == EWOULDBLOCK)
				|| (errno == EBADF) || (errno == EFAULT) || (errno == EINTR)
				|| (errno == EINVAL) || (errno == EIO)))
			return (fdf_generic_error(fdf));
		if (fdf->line == NULL)
			fdf->stop = 0;
		(fdf->height)++;
		if (fdf->line != NULL)
			fdf_get_width(fdf);
		free(fdf->line);
	}
	if (close(fdf->fd) < 0)
		return (fdf_generic_error(fdf));
	return (fdf->height);
}
