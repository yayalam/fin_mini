#include "../../minishell.h"

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(char c)
{
	return (c >= 0 && c <= 9);
}

int	check_equal_sign(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '=') == ft_strlen(arg[i]) - 1)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_split_for_env(char *arg)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * 3);
	i = ft_strchr(arg, '=');
	tmp[0] = ft_substr(arg, 0, i);
	tmp[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	tmp[2] = 0;
	if (!tmp || !tmp[0] || !tmp[1])
		return (NULL);
	return (tmp);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}