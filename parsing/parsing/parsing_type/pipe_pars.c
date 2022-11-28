#include "../../../minishell.h"

t_one_node_tree	*pipe_parse_handler(t_one_element **ptr)
{
	t_one_node_tree	*tmp;

	tmp = ft_calloc(sizeof(t_one_node_tree), 1);
	if (!tmp)
		return (NULL);
	tmp->type = PIPE;
	tmp->content = malloc(sizeof(t_cmd_or_pipe));
	tmp->content->pipe = malloc(sizeof(t_node_pipe));
	tmp->content->pipe->left = ft_calloc(sizeof(t_one_node_tree), 1);
	tmp->content->pipe->right = ft_calloc(sizeof(t_one_node_tree), 1);
	if (!tmp->content->pipe->right || !tmp->content->pipe->left)
		return (NULL);
	*ptr = (*ptr)->next;
	while ((*ptr)->type == SPACE)
		*ptr = (*ptr)->next;
	return (tmp);
}