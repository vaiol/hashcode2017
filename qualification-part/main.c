#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_video
{
	int 			id;
	struct s_video	*next;
}					t_video;

typedef struct		s_server
{
	int 			memory;
	t_video			*videos;

}					t_server;

typedef struct		s_request
{
	int 			count;
	int				v_id;
	int 			e_id;
}					t_request;

typedef struct		s_cache
{
	int				id;
	int 			latency;

} 					t_cache;

typedef	struct		s_endpoint
{
	int				data_latency;
	int 			cache_count;
	t_cache			**c_arr;
}					t_endpoint;


int v_count, e_count, r_count, c_count, c_capacity;

int 		videoExist(t_server *server, t_video *video)
{
	t_video *list = server->videos;
	while (list)
	{
		if (list->id == video->id)
			return (0);
		list = list->next;
	}
	return (1);
}

int 		addVideo(t_server *server, t_video *video, int v_memory)
{
	if (v_memory <= server->memory && videoExist(server, video))
	{
		server->memory -= v_memory;
		video->next = server->videos;
		server->videos = video;
		return (1);
	}
	return (0);

}

int			requestCmp(const void *a, const void *b)
{
	int i1 = (*((t_request **)b))->count;
	int i2 = (*((t_request **)a))->count;
	return (i1 - i2);
}

int			cacheCmp(const void *a, const void *b)
{
	return ((*((t_cache **)a))->latency - (*((t_cache **)b))->latency);
}

t_request	*createRequest(int count, int v_id, int e_id)
{
	t_request *request = (t_request *)malloc(sizeof(t_request));
	request->count = count;
	request->v_id = v_id;
	request->e_id = e_id;
	return (request);
}

t_server	*createServer(void)
{
	t_server *server = (t_server *)malloc(sizeof(t_server));
	server->memory = c_capacity;
	server->videos = NULL;
	return (server);
}

t_video		*createVideo(int id)
{
	t_video *video = (t_video *)malloc(sizeof(t_video));
	video->id = id;
	video->next = NULL;
	return (video);
}

t_cache		*createCache(int id, int latency)
{
	t_cache *cache = (t_cache *)malloc(sizeof(t_cache));
	cache->id = id;
	cache->latency = latency;
	return (cache);
}

t_endpoint	*createEndpoint(int data_latency, int cache_count, t_cache **c_arr)
{
	t_endpoint *endpoint = (t_endpoint *)malloc(sizeof(t_endpoint));
	endpoint->cache_count = cache_count;
	endpoint->data_latency = data_latency;
	endpoint->c_arr = c_arr;
	return (endpoint);
}

void		printInput(int *v_arr, t_endpoint **e_arr, t_request **r_arr)
{
	printf("%d %d %d %d %d\n", v_count, e_count, r_count, c_count, c_capacity);
	for (int i = 0; i < v_count; i++)
		printf("%d ", v_arr[i]);
	printf("\n");
	for (int i = 0; i < e_count; i++)
	{
		printf("%d %d\n", e_arr[i]->data_latency, e_arr[i]->cache_count);
		for (int j = 0; j < e_arr[i]->cache_count; j++)
			printf("%d %d\n", e_arr[i]->c_arr[j]->id, e_arr[i]->c_arr[j]->latency);
	}
	for (int i = 0; i < r_count; i++)
		printf("%d %d %d\n", r_arr[i]->v_id, r_arr[i]->e_id, r_arr[i]->count);
}

void		mary(int *v_arr, t_endpoint **e_arr, t_request **r_arr, FILE *res)
{
	t_server **s_arr = (t_server **)malloc(sizeof(t_server *) * c_count);
	for (int i = 0; i < c_count; i++)
		s_arr[i] = createServer();

	for (int i = 0; i < r_count; i++)
	{
		int e_id = r_arr[i]->e_id;
		int v_id = r_arr[i]->v_id;
		int v_mem = v_arr[v_id];
		if (v_mem > c_capacity)
			continue;
		for (int j = 0; j < e_arr[e_id]->cache_count; j++)
		{
			int cacheIndex = e_arr[e_id]->c_arr[j]->id;
			if (addVideo(s_arr[cacheIndex], createVideo(v_id), v_mem))
				break;
		}
	}
	int count = 0;
	for (int i = 0; i < c_count; i++)
	{
		if (s_arr[i]->videos != NULL)
			count++;
	}
	fprintf(res, "%d\n", count);
	for (int i = 0; i < c_count; i++)
	{
		if (s_arr[i]->videos != NULL)
		{
			fprintf(res, "%d ", i);
			t_video *video = s_arr[i]->videos;
			while (video)
			{
				fprintf(res, "%d ", video->id);
				video = video->next;
			}
			fprintf(res, "\n");
		}
	}
}

int	main(int argc, char **argv)
{
	FILE *fp = fopen(argv[1], "r");
	char *name = argv[1];
	while (*name != '.')
		name++;
	*name = '\0';
	strcat(argv[1], ".ou");
	FILE *res = fopen(argv[1], "w+");
	fscanf(fp, "%d %d %d %d %d\n", &v_count, &e_count, &r_count, &c_count,
		   &c_capacity);
	int *v_arr = (int *)malloc(sizeof(int) * v_count);
	for (int i = 0; i < v_count; i++)
	{
		fscanf(fp, " %d", &v_arr[i]);
	}
	t_endpoint **e_arr = (t_endpoint **)malloc(sizeof(t_endpoint *) * e_count);
	for (int i = 0; i < e_count; i++)
	{
		int data_latency, cache_count;
		fscanf(fp, "%d %d\n", &data_latency, &cache_count);
		t_cache **c_arr = (t_cache **)malloc(sizeof(t_cache *) * cache_count);
		for (int j = 0; j < cache_count; j++)
		{
			int id, latency;
			fscanf(fp, "%d %d\n", &id, &latency);
			c_arr[j] = createCache(id, latency);
		}
		qsort(c_arr, (size_t)cache_count, sizeof(t_cache *), cacheCmp);
		e_arr[i] = createEndpoint(data_latency, cache_count, c_arr);
	}
	t_request **r_arr = (t_request **)malloc(sizeof(t_request *) * r_count);
	for (int i = 0; i < r_count; i++)
	{
		int count, v_id, e_id;
		fscanf(fp, "%d %d %d\n", &v_id, &e_id, &count);
		r_arr[i] = createRequest(count, v_id, e_id);
	}
	qsort(r_arr, (size_t)r_count, sizeof(t_request *), requestCmp);
	fclose(fp);
//	printInput(v_arr, e_arr, r_arr);
	mary(v_arr, e_arr, r_arr, res);
	fclose(res);
	return (0);
}
