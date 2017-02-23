#include "pizza.h"

char	**getMap(FILE * fp, char *name, size_t rows, size_t columns)
{
	char	**map;
	char 	tmp;

	map = (char **)malloc(sizeof(char *) * (rows + 1));
	size_t i = 0;
	for (i = 0; i < rows; i++)
	{
		map[i] = (char *)malloc(sizeof(char) * (columns + 1));
		for (size_t j = 0; j <= columns; j++)
		{
			fscanf(fp, "%c", &tmp);
			if (tmp == '\n')
				map[i][j] = '\0';
			else
				map[i][j] = tmp;
		}
	}
	map[i] = NULL;
	return (map);
}


