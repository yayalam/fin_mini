#include "../minishell.h"

void	add_back_element_redir(t_head_redir *head, t_one_red_element *new)
{
	if (!head->head)
		head->head = new;
	else
		head->tail->next = new;
	head->tail = new;
	head->size++;
}

t_one_red_element	*creat_element_redir(char *arg, int type)
{
	t_one_red_element	*tmp;

	tmp = ft_calloc(sizeof(t_one_red_element), 1);
	if (!tmp)
		return (NULL);
	tmp->arg = arg;
	tmp->type = type;
	return (tmp);
}

t_head_redir	*redir_head_lst_init(t_head_redir *head)
{
	head = ft_calloc(sizeof(t_head_redir), 1);
	if (!head)
		return (NULL);
	return (head);
}

void	free_redir_list(t_head_redir *head)
{
	t_one_red_element	*tmp;

	tmp = head->head;
	while (tmp)
	{
		free(tmp->arg);
		free(tmp);
		tmp = tmp->next;
	}
	free(head);
}
