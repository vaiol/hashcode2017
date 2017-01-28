#ifndef PIZZA_H
#define PIZZA_H

#include <stdlib.h>
#include <stdio.h>

typedef	struct	s_rectangle
{
	size_t	length;
	size_t	width;
}		t_rectangle;

t_rectangle	**getRectangle(size_t min_cells, size_t max_cells);

#endif
