#include "../minishell.h"
void	del_one_element_env(t_all_env *env, t_env_one_element *elem)
{
	if (elem && elem->next)
		elem->next->prev = elem->prev;
	if (elem && elem->prev)
		elem->prev->next = elem->next;
	env->size--;
	free(elem->key);
	free(elem->value);
	free(elem);
	elem = NULL;
}

void	free_all_srtuct_env(t_all_env *env)
{
	t_env_one_element	*tmp;

	tmp = env->head;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = tmp->next;
	}
	free(env);
}

char	**from_struct_to_array(t_all_env *env)
{
	t_env_one_element	*tmp;
	char		**arr;
	int			i;

	i = 0;
	tmp = env->head;
	arr = ft_calloc(env->size + 1, sizeof(char *));
	if (arr)
	{
		while (i < env->size)
		{
			arr[i] = ft_strdup(tmp->key);
			if (tmp->value)
			{
				arr[i] = ft_strjoin(arr[i], "=");
				arr[i] = ft_strjoin(arr[i], tmp->value);
			}
			tmp = tmp->next;
			i++;
		}
		arr[i] = NULL;
	}
	return (arr);
}
