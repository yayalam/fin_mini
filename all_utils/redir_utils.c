#include "../minishell.h"

void	quotes_redir_counter(t_one_element **one_ele, int type, int *i)
{
	if (type == DOUBLE_QUOTE || type == QOUTE)
	{
		(*one_ele) = (*one_ele)->next;
		while ((*one_ele) && (*one_ele)->type != type)
			(*one_ele) = (*one_ele)->next;
		(*i)++;
	}
	else if (check_if_redir(type))
	{
		while ((*one_ele)->type != WORD && (*one_ele)->type != DOLLAR)
			(*one_ele) = (*one_ele)->next;
		(*one_ele) = (*one_ele)->next;
	}
}

int	check_if_redir(int type)
{
	return (type == IN_REDIR || type == OUT_REDIR
		|| type == DOUBLE_OUT || type == HERE_DOC);
}

char	*check_redir_type(int type)
{
	if (type == IN_REDIR)
		return ("<");
	if (type == OUT_REDIR)
		return (">");
	if (type == HERE_DOC)
		return ("<<");
	if (type == DOUBLE_OUT)
		return (">>");
	return (".");
}