#include "../minishell.h"
void	parse_free(t_tree_root *head)
{
	free_tree(head->root);
	free(head);
}

void	lexer_free(t_lexer_lst *lex)
{
	free_lexer_all_struct(lex);
}

void	parse_lex_free(t_lexer_lst *lex, t_tree_root *head)
{
	lexer_free(lex);
	parse_free(head);
}

void	cmd_free(t_one_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free_redir_list(cmd->redir);
	free(cmd);
}

void	double_dimension_free(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}
