#include "../../minishell.h"

char	*ft_strndup(char *s1,int n)
{
	int		i;
	char	*r;

	i = 0;
	while (s1[i])
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*r;

	i = 0;
	while (s1[i])
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*r;

	i = 0;
	r = NULL;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		start = ft_strlen(s);
	if (len >= (unsigned int)ft_strlen(s))
		len = ft_strlen(s);
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	while (i < (unsigned int)len)
	{
		r[i] = s[start];
		i++;
		start++;
	}
	r[i] = '\0';
	return (r);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (!num)
		return (0);
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}