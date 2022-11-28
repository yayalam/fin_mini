#include "../minishell.h"
int	check_redir_err(t_one_element *elem)
{
	t_one_element	*next;

	next = white_space_skipper(elem->next, 1);
	if (!next || (next->type != WORD && next->type != DOLLAR))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_pipe_err(t_one_element *elem)
{
	t_one_element	*prev;
	t_one_element	*next;

	prev = white_space_skipper(elem->prev, 0);
	next = white_space_skipper(elem->next, 1);
	if ((!prev || !next) || (prev->type != WORD
			&& next->type != WORD && !check_if_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
