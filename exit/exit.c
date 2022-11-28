#include "../minishell.h"
int	ft_exit(t_one_cmd *cmd, char **env)
{
	lexer_free(g_data.lex);
	free_all_srtuct_env(g_data.ev);
	if (g_data.alloc)
		double_dimension_free(env);
	printf("exit\n");
	if (check_exit_arg(cmd->args))
		return (1);
	g_data.exit_status = ft_atoi(cmd->args[1]);
	parse_free(g_data.tree);
	exit(g_data.exit_status);
	return (EXIT_SUCCESS);
}
