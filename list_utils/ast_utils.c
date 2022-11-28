#include "../minishell.h"
t_tree_root	*init_tree(t_tree_root *root)
{
	root = malloc(sizeof(t_tree_root));
	if (!root)
		return (NULL);
	root->root = NULL;
	return (root);
}

int	counter_number_of_cmds(t_one_node_tree *head)
{
	static int	size;

	if (head->type == CMD)
		size++;
	else
	{
		counter_number_of_cmds(head->content->pipe->right);
		counter_number_of_cmds(head->content->pipe->left);
	}
	return (size);
}

void	free_tree(t_one_node_tree *elem)
{
	if (elem->type == CMD)
	{
		cmd_free(elem->content->cmd);
		free(elem->content);
		free(elem);
	}
	else if (elem->type == PIPE)
	{
		free_tree(elem->content->pipe->right);
		free_tree(elem->content->pipe->left);
		free(elem->content->pipe);
		free(elem->content);
		free(elem);
	}
}

t_one_node_tree	*init_new_cmd_node(char **arg, char **env, t_head_redir *red)
{
	t_one_node_tree	*node;

	node = malloc(sizeof(t_one_node_tree));
	node->content = malloc(sizeof(t_cmd_or_pipe));
	node->content->cmd = malloc(sizeof(t_one_cmd));
	if (!node || !node->content || !node->content->cmd)
		return (NULL);
	node->type = CMD;
	node->content->cmd->args = arg;
	node->content->cmd->env = env;
	node->content->cmd->redir = red;
	node->content->cmd->fd.in = 0;
	node->content->cmd->fd.out = 1;
	return (node);
}

