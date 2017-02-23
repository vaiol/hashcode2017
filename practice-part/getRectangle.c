/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getRectangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbodak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:00:48 by mbodak            #+#    #+#             */
/*   Updated: 2017/01/30 19:22:54 by mbodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pizza.h"

t_rectangle		**getRectangle(size_t min_cells, size_t max_cells)
{
	t_rectangle		**rect;
	size_t			j;

    j = 0;
    for (size_t length = 1; length <= max_cells; length++)
    {
		for (size_t width = 1; width <= max_cells; width++)
		{
			if ((length * width) <= max_cells && (length * width) >= min_cells)
				j++;
		}
    }
    rect = (t_rectangle **)malloc(sizeof(t_rectangle *) * (j + 1));
	j = 0;
	for (size_t length = 1; length <= max_cells; length++)
	{
		for (size_t width = 1; width <= max_cells; width++)
		{
			if ((length * width) <= max_cells && (length * width) >= min_cells)
			{
				rect[j] = (t_rectangle *)malloc(sizeof(t_rectangle));
				rect[j]->length = length;
				rect[j]->width = width;
				j++;
			}
		}
	}
	rect[j] = NULL;
	return (rect);
}
