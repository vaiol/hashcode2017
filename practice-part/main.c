#include "pizza.h"

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
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	array = getRectangle(min, max);
	for (size_t i = 0; array[i]; i++)
		printf("%zu %zu\n", array[i]->length, array[i]->width);
	return (0);
}
