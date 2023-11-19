/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:44:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/19 11:01:49 by fporciel         ###   ########.fr       */
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

int	fdf_invalid_argument_error(void)
{
	return (perror(strerror(EINVAL)), 0);
}

int	fdf_nonexistent_file_error(void)
{
	return (perror(strerror(errno)), exit(EXIT_FAILURE), 0);
}

int	fdf_generic_error(t_fdf *fdf)
{
	int	ret;

	if (fdf == NULL)
		return (perror(strerror(errno)), exit(EXIT_FAILURE), 0);
	ret = fdf_memory_cleaner(fdf);
	return (perror(strerror(errno)), exit(EXIT_FAILURE), ret);
}
