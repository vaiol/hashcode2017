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

	if (argc != 3)
	{
		printf("error\n");
		return (1);
	}
	min = (size_t)atoi(argv[1]);
	max = (size_t)atoi(argv[2]);
	array = getRectangle(min, max);
	for (size_t i = 0; array[i]; i++)
		printf("%zu %zu\n", array[i]->length, array[i]->width);
	return (0);
}
