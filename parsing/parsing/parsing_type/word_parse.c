#include "../../../minishell.h"

void	word_parse_handler(t_one_element **ptr, char **arg, int *i)
{
	arg[*i] = ft_strndup((*ptr)->content, (*ptr)->len);
	(*i)++;
	(*ptr) = (*ptr)->next;
}