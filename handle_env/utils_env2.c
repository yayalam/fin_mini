#include "../minishell.h"
void	env_var_handler(t_all_env *env, t_one_cmd *cmd, t_one_element *head)
{
	char		**tmp;
	int			i;
	int			j;
	int			index;

	i = 1;
	tmp = NULL;
	while (cmd->args[i])
	{
		j = 0;
		j += ft_strjoin_export(&cmd, search_key_all_env(head, cmd->args[i],
					from_struct_to_array(env)), from_struct_to_array(env), i);
		index = ft_strchr(cmd->args[i], '=');
		check_index(env, cmd->args[i], tmp, index);
		if (!j)
			i++;
		else
			i += j;
	}
}

t_one_element	*search_key_all_env(t_one_element *head, char *arg, char **env)
{
	t_one_element	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == DOLLAR)
		{
			if (ft_strcmp(env_value_expand(tmp->content, env), arg) == EQUAL)
				break ;
		}
		if (ft_strcmp(tmp->content, arg) == EQUAL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	swap_env_elem(t_env_one_element *from, t_env_one_element *to)
{
	char	*key;
	char	*val;

	key = from->key;
	val = from->value;
	from->key = to->key;
	from->value = to->value;
	to->key = key;
	to->value = val;
}

void	delete_env_for_unset(char *arg, t_all_env *env)
{
	t_env_one_element	*element;

	element = NULL;
	if (arg && !ft_isalpha(arg[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			arg);
		g_data.exit_status = EXIT_FAILURE;
	}
	else
	{
		element = search_element_struct_env(env, arg);
		if (element)
			del_one_element_env(env, element);
	}
}

void	expand_env_element(t_one_element **ptr, t_all_env *env, char **args, int *i)
{
	args[*i] = get_value_of_env((*ptr)->content + 1, env);
	if (args[*i])
		(*i)++;
	(*ptr) = (*ptr)->next;
}