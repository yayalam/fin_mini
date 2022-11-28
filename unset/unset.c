#include "../minishell.h"

int	ft_unset(t_one_cmd *cmd, char ***env_2d)
{
	t_all_env	*env;
	int		i;

	i = 1;
	env = NULL;
	env = create_all_env_struct(*env_2d);
	g_data.exit_status = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		delete_env_for_unset(cmd->args[i], env);
		i++;
	}
	*env_2d = from_struct_to_array(env);
	free_all_srtuct_env(env);
	return (g_data.exit_status);
}
