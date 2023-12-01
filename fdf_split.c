/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:21:09 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/01 09:49:39 by fporciel         ###   ########.fr       */
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

static size_t	fdf_count_words(const char *str)
{
	size_t	count;
	size_t	num;

	count = 0;
	num = 0;
	while (str[count])
	{
		if ((str[count] > 32)
			&& ((count == 0) || (str[count - 1] <= 32)))
			num++;
		count++;
	}
	return (num);
}

static char	**fdf_clean_split(char **split, size_t words)
{
	size_t	count;

	count = 0;
	if (words == count)
		return (free(split), NULL);
	while (count < words)
	{
		free(split[count]);
		split[count] = NULL;
		count++;
	}
	free(split);
	return (NULL);
}

static char	*fdf_create_string(char *split, const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen] && ((str[strlen] >= 48) && (str[strlen] <= 57)))
		strlen++;
	split = (char *)malloc(sizeof(char) * (strlen + 1));
	if (split == NULL)
		return (NULL);
	strlen = 0;
	while (str[strlen] && ((str[strlen] >= 48) && (str[strlen] <= 57)))
	{
		split[strlen] = str[strlen];
		strlen++;
	}
	split[strlen] = 0;
	return (split);
}

static char	**fdf_fill_split(char **split, const char *str)
{
	size_t	count;
	ssize_t	words;

	count = 0;
	words = -1;
	while (str[count])
	{
		if ((str[count] > 32)
			&& ((count == 0) || (str[count - 1] <= 32)))
		{
			words++;
			split[words] = NULL;
			split[words] = fdf_create_string(split[words], &(str[count]));
			if (split[words] == NULL)
				return (fdf_clean_split(split, words));
		}
		count++;
	}
	return (split);
}

char	**fdf_split(const char *str)
{
	size_t	words_num;
	char	**split;

	if (str == NULL)
		return (NULL);
	words_num = fdf_count_words(str);
	split = (char **)malloc((words_num + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	split = fdf_fill_split(split, str);
	if (split == NULL)
		return (NULL);
	split[words_num] = NULL;
	return (split);
}
