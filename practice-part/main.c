#include "pizza.h"

static int  g_max;
static int  g_min;

int         getMax()
{
    return (g_max);
}

int         getMin()
{
    return (g_min);
}

int	main(int argc, char **argv)
{
	size_t		min;
	size_t		max;
	t_rectangle	**array;

	if (argc != 2)
	{
		printf("error\n");
		return (1);
	}
	char	*name = argv[1];
	size_t	rows;
	size_t	columns;
	size_t	piece;
	size_t	max_cells;
	size_t	min_cells;
	char	**map;

	FILE * fp = fopen(name, "r");
	fscanf(fp, "%zu %zu %zu %zu\n", &rows, &columns, &piece, &max_cells);
	min_cells = 2 * piece;
	map = getMap(fp, name, rows, columns);
	fclose(fp);
	//---------------
	printf("%zu %zu %zu %zu\n", rows, columns, piece, max_cells);
	for (size_t i = 0; map[i]; i++)
		printf("%s\n", map[i]);
	array = getRectangle(min_cells, max_cells);
	printf("\n");
	for (size_t i = 0; array[i]; i++)
		printf("%zu %zu\n", array[i]->length, array[i]->width);
	return (0);
}
