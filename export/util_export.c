#include "../minishell.h"
void	state_handler(t_one_element **head, char **env, int *value)
{
	if ((*head)->state == GENERAL)
	{
		(*value)++;
		if ((*head)->type == DOLLAR)
		{
			if (ft_strcmp(env_value_expand((*head)->content, env), "") == EQUAL)
				(*value)--;
		}
	}
	else
	{
		while ((*head) && (*head)->state != GENERAL)
			(*head) = (*head)->next;
		(*value)++;
	}
}

int	check_export_cmd(t_one_element *head, char **env)
{
	int	value;

	value = 0;
	while (head && head->type != PIPE && !check_if_redir(head->type)
		&& head->type != SPACE)
	{
		if (head->type == WORD || head->type == DOLLAR)
			state_handler(&head, env, &value);
		head = head->next;
	}
	return (value);
}

void	sort_env_for_export(t_all_env *env)
{
	t_env_one_element	*tmp;

	tmp = env->head;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, tmp->next->key) > 0)
		{
			swap_env_elem(tmp, tmp->next);
			tmp = env->head;
		}
		else
			tmp = tmp->next;
	}
}

void	print_env_sorted_export_noparam(t_all_env *env)
{
	t_all_env		*head;
	t_env_one_element	*element;

	head = env;
	sort_env_for_export(head);
	element = head->head;
	while (element)
	{
		printf("declare -x %s", element->key);
		if (element->value)
			printf("=\"%s\"", element->value);
		printf("\n");
		element = element->next;
	}
}

void	check_index(t_all_env *env, char *arg, char **tmp, int index)
{
	t_env_one_element	*element;

	element = NULL;
	if (index != -1)
	{
		tmp = ft_split_for_env(arg);
		element = search_element_struct_env(env, tmp[0]);
		if (element)
		{
			free(element->value);
			element->value = ft_strdup(tmp[1]);
		}
		else
			add_env_elem(env, create_new_elem_env(arg));
		double_dimension_free(tmp);
	}
	else
	{
		element = search_element_struct_env(env, arg);
		if (!element)
			add_env_elem(env, create_new_elem_env(arg));
	}
}