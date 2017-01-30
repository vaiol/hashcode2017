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
	size_t			i;
	size_t			j;
    size_t			k;
	size_t			length;
	size_t			width;
		
    i = 0;
    j = 0;
    k = 0;
    length = 1;
    while (length <= max_cells)
    {
        if (length == 1)
            width = min_cells;
        else
            width = 1;
        while (width <= max_cells && (length * width) <= max_cells && (length * width) >= min_cells)
        {
            k = length * width;
            width++;
            j++;
        }
        length++;
        i++;
    }
    rect = (t_rectangle **)malloc(sizeof(t_rectangle *) * (j + 1));
	i = 0;
	j = 0;
	length = 1;
	while (length <= max_cells)
	{
		if (length == 1)
			width = min_cells;
		else
			width = 1;
		while (width <= max_cells && (length * width) <= max_cells && (length * width) >= min_cells)
		{
			rect[j] = (t_rectangle *)malloc(sizeof(t_rectangle));
			rect[j]->length = length;
			rect[j]->width = width++;
			j++;
		}
		length++;
		i++;
	}
	rect[j] = NULL;
	return (rect);
}
