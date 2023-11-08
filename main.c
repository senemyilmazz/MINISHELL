
#include <stdio.h>
#include <stdlib.h>
size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (c)
	{
		while (c[i])
			i++;
	}
	return (i);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*source;
	size_t	i;

	dest = (char *)dst;
	source = (char *)src;
	i = -1;
	if (n == 0 || dest == source)
		return (dest);
	while (++i < n)
		dest[i] = source[i];
	return ((void *)dest);
}


char	*ft_strdup(const char *s1)
{
	char	*coppiedarray;
	size_t	len;

	len = ft_strlen(s1) + 1;
	coppiedarray = malloc(len * sizeof(char));
	if (!coppiedarray)
		return (NULL);
	coppiedarray = (char *)ft_memcpy(coppiedarray, s1, len);
	return (coppiedarray);
}

char	**dynamic_malloc(char **path, char *new)
{
	int		count;
	char	**new_path;
	int		i;

	count = 0;
	while (path[count])
		count++;
	new_path = (char **)malloc(sizeof(char *) * count + 2);
	if (!new_path)
		return (NULL);
	i = -1;
	while (++i < count)
		new_path[i] = ft_strdup(path[i]);
	new_path[i++] = ft_strdup(new);
	new_path[i] = NULL;
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (new_path);
}


int main()
{
	char **path = malloc(sizeof(char *) * 3);
	path[0] = ft_strdup("senem");
	path[1] = ft_strdup("yilmaz");
	path[2] = NULL;
	int i = -1;
	while (path[++i])
		printf("%s\n", path[i]);
	printf("--------\n");
	path = dynamic_malloc(path, "gokcem");
	i = -1;
	while (path[++i])
		printf("%s\n", path[i]);
	system("leaks a.out");
}