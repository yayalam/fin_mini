#include "../../minishell.h"

int	my_parser(t_tree_root **head, t_one_element *ptr, t_all_env *env)
{
	t_one_node_tree	*tmp_node;

	tmp_node = NULL;
	if (!ptr)
		return (EXIT_FAILURE);
	tmp_node = cmd_parser(&ptr, env);
	if (!tmp_node)
		return (EXIT_FAILURE);
	if (!(*head)->root)
		(*head)->root = tmp_node;
	else
	{
		if (!(*head)->root->content->pipe->right)
			(*head)->root->content->pipe->right = tmp_node;
		else
			(*head)->root->content->pipe->left = tmp_node;
	}
	if (ptr && ptr->type == PIPE)
	{
		tmp_node = pipe_parse_handler(&ptr);
		tmp_node->content->pipe->right = (*head)->root;
		(*head)->root = tmp_node;
	}
	my_parser(head, ptr, env);
	return (EXIT_SUCCESS);
}
