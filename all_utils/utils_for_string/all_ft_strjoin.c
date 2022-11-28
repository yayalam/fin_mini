#include "../../minishell.h"

int	ft_strjoin_echo(t_one_cmd **cmd, t_one_element *head, char **env, int i)
{
	int	j;
	int	val;

	j = 0;
	val = echo_cmd_check(head, env);
	while (++j < val && (*cmd)->args[i + j])
		(*cmd)->args[i] = ft_strjoin((*cmd)->args[i], (*cmd)->args[i + j]);
	return (val);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*p;
	int		p_len;
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = (char *)malloc (1 * sizeof(char));
		s1[0] = 0;
	}
	p_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(sizeof(char) * p_len);
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*ft_strjoin_directory(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1) + 1;
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '/';
	i = 0;
	while (s2[i])
		str[len1++] = s2[i++];
	str[len1] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		p_len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	p_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(sizeof(char) * p_len);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

int	ft_strjoin_export(t_one_cmd **cmd, t_one_element *head, char **env, int i)
{
	int	j;
	int	val;

	j = 0;
	val = check_export_cmd(head, env);
	while (++j < val && (*cmd)->args[i + j])
		(*cmd)->args[i] = ft_strjoin((*cmd)->args[i], (*cmd)->args[i + j]);
	double_dimension_free(env);
	return (val);
}