#include "../minishell.h"

t_all_env	*init_env(t_all_env *env)
{
	env = ft_calloc(sizeof(t_all_env), 1);
	if (!env)
		return (NULL);
	return (env);
}

t_env_one_element	*create_new_elem_env(char *line)
{
	t_env_one_element	*elem;
	char		*key;
	char		*value;
	int			index;

	index = ft_strchr(line, '=');
	elem = ft_calloc(sizeof(t_env_one_element), 1);
	if (index != -1)
	{
		key = ft_substr(line, 0, index);
		value = ft_substr(line, index + 1, ft_strlen(line) - index);
		if (!key || !value || !elem)
			return (NULL);
		elem->key = key;
		elem->value = value;
	}
	else
	{
		elem->key = ft_strdup(line);
		elem->value = NULL;
	}
	return (elem);
}

void	add_env_elem(t_all_env *env, t_env_one_element *new)
{
	t_env_one_element	*tmp;

	tmp = env->head;
	if (!env->head)
		env->head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	env->size++;
}

t_all_env	*create_all_env_struct(char **tab)
{
	t_all_env	*env;
	int		i;	

	env = NULL;
	env = init_env(env);
	env->env = tab;
	i = 0;
	while (tab[i])
		add_env_elem(env, create_new_elem_env(tab[i++]));
	return (env);
}
