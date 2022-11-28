#include "../minishell.h"
int	ft_export(char ***env, t_one_cmd *cmd, t_one_element *head)
{
	t_all_env	*tmp;

	tmp = NULL;
	tmp = create_all_env_struct(*env);
	if (!cmd->args[1])
		print_env_sorted_export_noparam(tmp);
	else
	{
		if (!ft_isalpha(cmd->args[1][0]))
			return (ft_puterr(cmd->args[0],
					cmd->args[1], "not a valid identifier", EXIT_FAILURE));
		env_var_handler(tmp, cmd, head);
		g_data.env = from_struct_to_array(tmp);
		*env = from_struct_to_array(tmp);
		g_data.alloc = 1;
	}
	free_all_srtuct_env(tmp);
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
