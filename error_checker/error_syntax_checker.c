#include "../minishell.h"
t_one_element	*check_quote_unclose(t_one_element **elem, int type)
{
	while (*elem)
	{
		*elem = (*elem)->next;
		if (!*elem || (*elem)->type == type)
			break ;
	}
	if (!*elem)
		write(STDERR_FILENO, "minishell: unclosed quotes detected.\n",
			ft_strlen("minishell: unclosed quotes detected.\n"));
	return (*elem);
}

t_one_element	*white_space_skipper(t_one_element *elem, int flag)
{
	while (elem && elem->type == SPACE)
	{
		if (flag)
			elem = elem->next;
		else
			elem = elem->prev;
	}
	return (elem);
}

int	check_err_syntax(t_lexer_lst *head)
{
	t_one_element	*ptr;

	ptr = head->head;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			if (check_pipe_err(ptr))
				return (ft_perror("minishell: syntax error near"
						"unexpected token `|'", NULL));
		}
		else if (check_if_redir(ptr->type))
		{
			if (check_redir_err(ptr))
				return (ft_perror("minishell: syntax error near"
						"unexpected token ", check_redir_type(ptr->type)));
		}
		else if (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE)
		{
			if (!check_quote_unclose(&ptr, ptr->type))
				return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
