#include "pizza.h"

t_slice     *createSlice(t_rectangle *rectangle, const size_t i, const size_t j)
{
    t_slice *result = (t_slice *)malloc(sizeof(t_slice));
    result->columns_start = j;
    result->rows_start = i;
    result->columns_end = j + rectangle->width;
    result->rows_end = i + rectangle->length;
    result->next = NULL;
    return (result);
}

t_slice     *addSlice(t_slice *list, t_slice *slice)
{
    if (list == NULL)
        return (slice);
    slice->next = list;
    return (slice);
}

t_slice     *removeSlice(t_slice *list)
{
    t_slice *slice;
    if (list == NULL)
        return (NULL);
    slice = list->next;
    free(list);
    return (slice);

}

int         checkSlices(t_slice *list, t_slice *slice)
{
    while (slice)
    {
        if ((list->columns_start > slice->columns_end || list->columns_end < slice->columns_start)
            || (list->rows_start > slice->rows_end || list->rows_end < slice->rows_start))
            return (0);
        slice = slice->next;
    }
    return (1);
}

int         checkFields(char **map, t_slice *slice, size_t piece)
{
    int m_count = 0;
    int t_count = 0;
    for (size_t i = slice->rows_start; i <= slice->rows_end; i++)
    {
        for (size_t j = slice->columns_start; j <= slice->columns_end; j++)
        {
            if (map[i][j] == 'T')
                t_count++;
            if (map[i][j] == 'M')
                m_count++;
        }
    }
    if (m_count < piece && t_count < piece)
        return (0);
    return (1);
}

void        printSlices(t_slice *slice)
{
    while (slice)
    {
        printf("%zu %zu %zu %zu\n", slice->rows_start, slice->columns_start, slice->rows_end, slice->columns_end);
        slice = slice->next;
    }
}

