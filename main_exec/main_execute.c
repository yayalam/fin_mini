#include "../minishell.h"

int	builtin_exec(t_one_node_tree *node, char ***env, t_one_element *head, int fd[2])
{
	int	pid;

	pid = 0;
	if (is_buitlin(node->content->cmd->args[0]) == 1)
		builtin_ex(node->content->cmd, env, head);
	else
		pid = cmd_executor(node->content->cmd, *env, fd);
	return (pid);
}

void	main_execute(t_one_node_tree *node, char ***env, int cmds_number, t_one_element *lexer_head)
{
	int			fd[2];
	int			pid;
	static int	count;

	pid = 0;
	if (node->type == CMD)
	{
		pid = builtin_exec(node, env, lexer_head, fd);
		count++;
	}
	else if (node->type == PIPE)
	{
		if (pipe(fd) < 0)
			return ;
		if (node->content->pipe->right->type == CMD)
			swap_fd_var(&node->content->pipe->right->content->cmd->fd.out, fd[1]);
		else if (node->content->pipe->right->type == PIPE)
			swap_fd_var(search_r_l(node), fd[1]);
		swap_fd_var(&node->content->pipe->left->content->cmd->fd.in, fd[0]);
		main_execute(node->content->pipe->right, env, cmds_number, lexer_head);
		main_execute(node->content->pipe->left, env, cmds_number, lexer_head);
		close(fd[0]);
		close(fd[1]);
	}
	check_last_pid(pid, count, cmds_number);
}
