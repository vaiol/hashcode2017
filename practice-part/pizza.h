#ifndef PIZZA_H
#define PIZZA_H

#include <stdlib.h>
#include <stdio.h>

typedef	struct		s_rectangle
{
	size_t			length;
	size_t			width;
}					t_rectangle;

typedef struct		s_slice
{
	t_rectangle		*rectangle;
	size_t 			rows_start;
	size_t			rows_end;
	size_t			columns_start;
	size_t			columns_end;
	struct s_slice	*next;

}					t_slice;


int                 getMax();
int                 getMin();
t_slice             *createSlice(t_rectangle *rectangle, size_t i, size_t j);
t_slice				*addSlice(t_slice *list, t_slice *slice);
t_slice				*removeSlice(t_slice *list);
void				printSlices(t_slice *slice);
t_rectangle			**getRectangle(size_t min_cells, size_t max_cells);

#endif
