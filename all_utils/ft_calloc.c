#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*p;
	size_t		i;

	i = 0;
	p = (void *)malloc(size * count);
	if (!p)
		return (NULL);
	while (i < count * size)
	{
		*(char *)p = 0;
		i++;
		p++;
	}
	return ((char *)p - i);
}