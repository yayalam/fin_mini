#include "../minishell.h"

char	*get_value_of_env(char *key, t_all_env *env)
{
	t_env_one_element	*elem;

	if (ft_strcmp(key, "?") == EQUAL || ft_strcmp(key, "?\n") == EQUAL)
		return (ft_itoa(g_data.exit_status));
	elem = search_element_struct_env(env, key);
	if (!elem)
		return (NULL);
	else
		return (ft_strdup(elem->value));
}

t_env_one_element	*search_element_struct_env(t_all_env *env, char *key)
{
	t_env_one_element	*tmp;

	tmp = env->head;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	return (tmp);
}

char	*search_element_array_env(char *key, char **env)
{
	int		i;
	int		pos;
	char	*var;

	i = 0;
	if (ft_strcmp(key, "?") == EQUAL)
		return (ft_itoa(g_data.exit_status));
	while (env[i] && ft_strncmp(env[i], key, ft_strlen(key)))
		i++;
	if (!env[i])
		return (NULL);
	pos = ft_strchr(env[i], '=');
	if (pos == -1)
		return (NULL);
	var = ft_substr(env[i], pos + 1, ft_strlen(env[i]) - (pos + 1));
	return (var);
}

char	*find_value_expand_env(char **line, char **env)
{
	int		key_len;
	char	key[500];

	key_len = 0;
	(*line)++;
	if (**line == '?')
		key[key_len++] = *((*line)++);
	else
	{
		while (**line && ft_isalnum(**line))
			key[key_len++] = *((*line)++);
	}
	key[key_len] = '\0';
	return (search_element_array_env(key, env));
}

char	*env_value_expand(char *line, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	res[1024];

	i = -1;
	value = NULL;
	while (line[++i] && line[i] != '$')
		res[i] = line[i];
	if (line[i] == '$')
	{
		line = line + i;
		value = find_value_expand_env(&line, env);
		if (value)
		{
			j = 0;
			while (value[j])
				res[i++] = value[j++];
		}
	}
	while (*line)
		res[i++] = *(line++);
	res[i] = '\0';
	return (ft_strdup(res));
}
