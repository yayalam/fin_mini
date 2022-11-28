#include "../../minishell.h"

int	arg_counter(t_one_element *one_elem)
{
	t_one_element	*tmp;
	int		i;

	i = 0;
	tmp = one_elem;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == DOLLAR)
			i++;
		else if (tmp->type == DOUBLE_QUOTE || tmp->type == QOUTE
			|| check_if_redir(tmp->type))
			quotes_redir_counter(&tmp, tmp->type, &i);
		if (tmp)
			tmp = tmp->next;
	}
	return (i);
}
