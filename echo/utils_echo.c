#include "../minishell.h"
int	if_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] != '-')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_echo_args(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!if_flag(arg[i]))
			return (i);
		i++;
		if (arg[i] == NULL)
			return (i);
	}
	return (-1);
}

int	echo_cmd_check(t_one_element *head, char **env)
{
	int	val;

	val = 0;
	while (head && head->type != PIPE
		&& !check_if_redir(head->type) && head->type != SPACE)
	{
		if (head->type == WORD || head->type == DOLLAR)
			cmd_state_check(&head, env, &val);
		head = head->next;
	}
	return (val);
}

void	add_number_to(int *i, int to_add)
{
	if (!to_add)
		(*i)++;
	else
		(*i) += to_add;
}

void	cmd_state_check(t_one_element **head, char **env, int *value)
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