#include "../minishell.h"

int	check_if_no_element(t_lexer_lst *head)
{
	return (head->head == NULL);
}

t_lexer_lst	*lexer_lst_init(t_lexer_lst *head)
{
	head = ft_calloc(sizeof(t_lexer_lst), 1);
	if (!head)
		return (NULL);
	return (head);
}

t_one_element	*create_new_lexer_element(char *cnt, int len, int type, int state)
{
	t_one_element	*elem;
	char	*tmp;

	elem = ft_calloc(sizeof(t_one_element), 1);
	if (!elem)
		return (NULL);
	tmp = ft_strndup(cnt, len);
	if (!tmp)
		return (NULL);
	elem->content = tmp;
	elem->len = len;
	elem->type = type;
	elem->state = state;
	return (elem);
}

void	add_lexer_element_back(t_lexer_lst *head, t_one_element *new)
{
	if (check_if_no_element(head))
		head->head = new;
	else
	{
		head->tail->next = new;
		new->prev = head->tail;
	}
	head->tail = new;
	head->size++;
}

void	free_lexer_all_struct(t_lexer_lst *head)
{
	t_one_element	*tmp;

	tmp = head->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(head);
}
